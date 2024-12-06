/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:38:23 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/06 18:10:16 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit
//unset
//export
//run

//echo -n (string), or, echo (string)
void	builtin_echo(t_minishell *mshell, t_list *lst)
{
	int	newline_flag;
	int	i;
	int	j;

	newline_flag = 1;
	i = -1;
	if (lst->lexem[1][0] == '-' && lst->lexem[1][1] == 'n')
	{
		newline_flag = 0;
		++i;
	}
	while (lst->lexem[++i])
	{
		j = -1;
		while (lst->lexem[i][++j])
		{
			
		}
	}
}


//change directory; deal w/ relative path or absolute path or default
//relative path: currect dir (./), parent dir (../) and subdirectory (*/)
//absolute path: path start w/ root
void	builtin_cd(t_minishell *mshell, t_list *lst)
{
	char	path[4096];

	if (lst->lexem[1])
	{
		if (lst->lexem[1][0] == '/')// ex. /usr/bin/ls
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
	else
		chdir(ft_getenv(mshell, "HOME"));
	mshell->exit_status = 0;
}

//print out all envinronment variables
//pop error msg when receive arguments
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

//print current work directory
void	builtin_pwd(t_minishell *mshell, t_list *lst)
{
	printf("%s\n", mshell->cwd);
	mshell->exit_status = 0;
}

void	built_in(t_minishell *mshell, t_list *lst)
{
	if (lst->lexem[0] == NULL)
		return ;
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
		builtin_pwd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		builtin_env(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		builtin_echo(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		builtin_exit(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		builtin_unset(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		builtin_cd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		builtin_export(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
				!ft_strncmp(lst->lexem[0], "/", 1))
		builtin_run(mshell, lst);
}
//beware the in & out fd
