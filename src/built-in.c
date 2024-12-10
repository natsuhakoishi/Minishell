/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:38:23 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/10 15:18:36 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle 'exit'
//>no option; no args / only-numeric args
void	builtin_exit(t_minishell *mshell, t_list *lst)
{
	int	i;

	i = -1;
	printf("exit\n");
	if (lst->lexem[1])
	{
		while (lst->lexem[1][++i])
		{
			if (!ft_isdigit(lst->lexem[1][i]))
			{
				ft_putstr_fd("Minishell: exit: ", 2);
				perror(lst->lexem[1]);
				mshell->exit_status = 2;
			}
			break ;
		}
		mshell->exit_status = ft_atoi(lst->lexem[1]);
		if (mshell->exit_status > 256)
			mshell->exit_status %= 256;
	}
	else
		mshell->exit_status = 0;
	free_exit(mshell, &lst);
}
//fix while loop break but didnt totally jump out the if statement, exit status will be wrong

//handle 'echo'
//>no arg / option -n
void	builtin_echo(t_minishell *mshell, t_list *lst)
{
	int	newline_flag;
	int	i;

	newline_flag = 1;
	i = -1;
	if (lst->lexem[1][0] == '-' && lst->lexem[1][1] == 'n' && !lst->lexem[1][2])
	{
		newline_flag = 0;
		i += 2;
	}
	while (lst->lexem[++i])
	{
		ft_putstr_fd(lst->lexem[i], 1);
		if (lst->lexem[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (newline_flag)
		ft_putstr_fd("\n", 1);
	mshell->exit_status = 0;
}
//fix didnt handle for multiple args

//handle 'cd'
//>no args / relative path / absolute path
//*relative path: homeD(~), currentD (./), parentD(../) & subdirectory (*/)
//*absolute path: full path starting w/ root
void	builtin_cd(t_minishell *mshell, t_list *lst)
{
	char	path[4096];

	if (lst->lexem[1])
	{
		if (lst->lexem[1][0] == '/') // ex. /usr/bin/ls
			chdir(lst->lexem[1]);
		else
		{
			ft_strlcpy(path, mshell->cwd, 100);
			ft_strlcat(path, "/", 100);
			ft_strlcat(path, lst->lexem[1], 100);
			if (!access(path, F_OK))
				chdir(path);
			else
			{
				printf("Minishell: cd: %s: No such file or directory", lst->lexem[1]);
				mshell->exit_status = 1;
				return ;
			}
		}
	}
	else if (!lst->lexem[1] || lst->lexem[1][0] == '~')
		chdir(ft_getenv(mshell, "HOME"));
	mshell->exit_status = 0;
}
//memo memory management for ft_strlcat()

//handle 'env' (no arg)
//*show err msg if there argument passed in
void	builtin_env(t_minishell *mshell, t_list *lst)
{
	int	i;

	i = -1;
	if (lst->lexem[1])
	{
		printf("env: '%s': No such file or directory\n", lst->lexem[1]);
		mshell->exit_status = 127;
		return ;
	}
	while (mshell->envp[++i])
	{
		if (ft_strchr(mshell->envp[i], '='))
			printf("%s\n", mshell->envp[i]);
	}
	mshell->exit_status = 0;
}

void	built_in(t_minishell *mshell, t_list *lst)
{
	if (lst->lexem[0] == NULL)
		return ;
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
	{
		printf("%s\n", mshell->cwd);
		mshell->exit_status = 0;
	}
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		builtin_exit(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		builtin_env(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		builtin_cd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		builtin_echo(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		builtin_unset(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		builtin_export(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
				!ft_strncmp(lst->lexem[0], "/", 1))
		executable(mshell, lst);
}
//memo pwd() not error handling, should have manage in previous stage
//memo should be able handle multiple argument passed in

//beware the in & out fd
//todo not enough error handling for some built-in? not sure
//todo exit_status checking; can replicate same error and 'echo $?' to check
////doubt deal w/ path only? the path resolution thing
//todo (should be include) //!ft_strncmp(lst->lexem[0], "../", 3) || !ft_strchr(lst->lexem[0], '/')