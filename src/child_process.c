/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:14:54 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/31 08:40:19 by zgoh             ###   ########.fr       */
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

	if (check_built_in(lst))
		return ;
	if (lst->lexem && lst->lexem[0])
	{
		path = get_path(mshell, lst);
		if (!ft_strncmp(lst->lexem[0], ".", 1) \
			|| !ft_strncmp(lst->lexem[0], "..", 2))
			path = NULL;
		if (!path)
		{
			err_msg(mshell, 127, "Minishell: '%s': command not found\n", \
					lst->lexem[0]);
			free(path);
			return ;
		}
		execve(path, lst->lexem, mshell->envp);
		free(path);
		mshell->exit_status = 1;
	}
}

int	input_setup(t_minishell *mshell, t_list *lst)
{
	if (lst->in_path && lst->delimiter == NULL)
		mshell->in_fd = open(lst->in_path, O_RDONLY);
	else if (lst->in_path == NULL && lst->delimiter)
		mshell->in_fd = open(".tmp", O_RDONLY);
	else if (lst->pipe_fd[0] != -1 && lst->pipe_fd[0] != 0)
		mshell->in_fd = lst->pipe_fd[0];
	else
		mshell->in_fd = dup(mshell->in_backup);
	if (mshell->here_doc && mshell->exit_status == 42)
		return (1);
	if (mshell->in_fd == -1 && !mshell->here_doc)
	{
		perror("Minishell: Infile");
		return (1);
	}
	if (dup2(mshell->in_fd, 0) == -1 && !mshell->here_doc)
	{
		perror("Error: infile fd");
		return (1);
	}
	close(mshell->in_fd);
	return (0);
}

void	output_setup(t_minishell *mshell, t_list *lst)
{
	if (lst->out_path && lst->append == 0)
		mshell->out_fd = open(lst->out_path, \
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (lst->out_path && lst->append == 1)
		mshell->out_fd = open(lst->out_path, \
							O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (lst->next)
	{
		mshell->out_fd = lst->next->pipe_fd[1];
		close(lst->next->pipe_fd[0]);
	}
	else
		mshell->out_fd = dup(mshell->out_backup);
	if (dup2(mshell->out_fd, 1) == -1)
	{
		perror("Error: outfile fd");
		return ;
	}
	close(mshell->out_fd);
}

void	child_process(t_minishell *mshell, t_list *lst)
{
	if (input_setup(mshell, lst) == 0)
	{
		if (mshell->here_doc)
			exit(mshell->exit_status);
		output_setup(mshell, lst);
		ft_signal(1);
		if (check_built_in(lst))
			built_in(mshell, lst);
		cmd(mshell, lst);
	}
	else
		mshell->exit_status = 1;
	exit(mshell->exit_status);
}
