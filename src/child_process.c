/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:14:54 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/13 18:38:21 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find the valid path based on args(lexem)
char	*get_path(t_minishell *mshell, t_list *lst)
{
	char	**env_paths;
	char	*temp;
	char	*path;
	int		i;

	i = -1;
	env_paths = ft_split(ft_getenv(mshell, "PATH"), ':');
	while (env_paths && env_paths[++i])
	{
		temp = ft_strjoin(env_paths[i], "/");
		path = ft_strjoin(temp, lst->lexem[0]);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_dptr(env_paths);
			return (path);
		}
		free(path);
	}
	free_dptr(env_paths);
	return (NULL);
}

void	cmd(t_minishell *mshell, t_list *lst)
{
	char	*path;

	if (lst->lexem && lst->lexem[0])
	{
		path = get_path(mshell, lst);
		if (!path)
		{
			ft_putstr_fd("Minishell: command not found:", 2);
			ft_putstr_fd(lst->lexem[0], 2);
			ft_putstr_fd("\n", 2);
			mshell->exit_status = 127;
			return ;
		}
		execve(path, lst->lexem, mshell->envp);
		mshell->exit_status = 1;
	}
}

void	input_setup(t_minishell *mshell, t_list *lst)
{
	if (lst->in_path)
		mshell->in_fd = open(lst->in_path, O_RDONLY);
	else if (lst->delimiter)
		mshell->in_fd = open(".tmp", O_RDONLY);
	else if (lst->pipe_fd[0] != -1 && lst->pipe_fd[0] != 0)
		mshell->in_fd = lst->pipe_fd[0];
	else
		mshell->in_fd = dup(mshell->in_backup);
	if (mshell->in_fd == -1)
	{
		perror("Minishell: can't open file\n");
		lst->in_path = NULL;
		exit(-1);
	}
	if (dup2(mshell->in_fd, 0) == -1)
	{
		perror("dup2: in fd\n");
		return ;
	}
	close(mshell->in_fd);
}

void	output_setup(t_minishell *mshell, t_list *lst)
{
	if (lst->out_path && !(lst->append))
		mshell->out_fd = open(lst->out_path, O_WRONLY | O_CREAT | O_TRUNC, \
			0777);
	else if (lst->out_path && lst->append)
		mshell->out_fd = open(lst->out_path, O_WRONLY | O_CREAT | O_APPEND, \
			0777);
	else if (lst->next)
	{
		mshell->out_fd = lst->next->pipe_fd[1];
		close(lst->next->pipe_fd[0]);
	}
	else
		mshell->out_fd = dup(mshell->out_backup);
	if (dup2(mshell->out_fd, 1) == -1)
	{
		perror("dup2: out fd\n");
		return ;
	}
	close(mshell->out_fd);
}
//todo proper file permission

void	child_process(t_minishell *mshell, t_list *lst)
{
	input_setup(mshell, lst);
	output_setup(mshell, lst);
	ft_signal(1);
	if (check_built_in(lst))
		built_in(mshell, lst);
	cmd(mshell, lst);
	// printf("hello\n");
	exit(mshell->exit_status);
}
//todo memo; first command / enter will hit debug line