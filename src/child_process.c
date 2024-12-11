/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:14:54 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/11 01:49:42 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//attempt to form a path & test w/ access() and execve()
void	get_path(t_minishell *mshell, t_list *lst, char **env_paths, int i)
{
	char	full_path[10000];

	ft_strlcpy(full_path, env_paths[i], 10000);
	ft_strlcat(full_path, "/", 10000);
	ft_strlcat(full_path, lst->lexem[0], 10000);
	if (access(full_path, F_OK | X_OK) == 0)
		execve(full_path, lst->lexem, mshell->envp);
	mshell->execve_status = -1;
}

//get environment varialble PATH, then throw one by one to getpath
int	check_executable(t_minishell *mshell, t_list *lst)
{
	char	**env_paths;
	// char	*path;
	int		i;

	i = -1;
	// path = NULL;
	env_paths = ft_split(ft_getenv(mshell, "PATH"), ':');
	while (env_paths && env_paths[++i])
	{
		get_path(mshell, lst, env_paths, i);
		if (mshell->execve_status == -1)
		{
			i = -1;
			while (env_paths[i])
				free (env_paths[i--]);
			free (env_paths);
			return (0);
		}
	}
	i = -1;
	while (env_paths[i])
		free (env_paths[i--]);
	free (env_paths);
	return (1);
}

void	cmd(t_minishell *mshell, t_list *lst)
{
	if (lst->lexem[0])
	{
		if (check_built_in(lst))
			return ;
		else if (!check_executable(mshell, lst))
		{
			ft_putstr_fd("Minishell: command not found:", 2);
			ft_putstr_fd(lst->lexem[0], 2);
			mshell->exit_status = 127;
		}
	}
}

void	child_process(t_minishell *mshell, t_list *lst)
{
	input_setup(mshell, lst);
	output_setup(mshell, lst);
	ft_signal(1);
	built_in(mshell, lst);
	cmd(mshell, lst);
	exit(mshell->exit_status);
}
