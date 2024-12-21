/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:38:23 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/21 12:30:54 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle cmd absolute path & executable file
void	executable(t_minishell *mshell, t_list *lst)
{
	pid_t	p_id;

	if (access(lst->lexem[0], F_OK | X_OK) == 0)
	{
		p_id = fork();
		if (p_id == 0)
			execve(lst->lexem[0], lst->lexem, mshell->envp);
		else if (p_id)
		{
			waitpid(p_id, &mshell->exit_status, 0);
			mshell->exit_status = WEXITSTATUS(mshell->exit_status);
		}
	}
	else
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(lst->lexem[0]);
		mshell->exit_status = 127;
		return ;
	}
}

//handle 'exit'
//>no option; no args / only-numeric args
void	builtin_exit(t_minishell *mshell, t_list *lst)
{
	int	i;

	i = -1;
	printf("exit\n");
	if (lst->lexem[1] && !lst->lexem[2])
	{
		while (lst->lexem[1][++i])
		{
			if (!ft_isdigit(lst->lexem[1][i]))
			{
				err_msg(mshell, 2, \
						"Minishell: exit: %s: numeric argument required\n", \
						lst->lexem[1]);
				free_exit(mshell, &lst, 0);
				return ;
			}
		}
		mshell->exit_status = ft_atoi(lst->lexem[1]);
		mshell->exit_status %= 256;
	}
	else if (lst->lexem[1] && lst->lexem[2])
		err_msg(mshell, 1, "Minishell: exit: too many arguments\n", NULL);
	else
		mshell->exit_status = 0;
	free_exit(mshell, &lst, 0);
}

//handle 'echo'
//>no arg / option -n
void	builtin_echo(t_minishell *mshell, t_list *lst)
{
	int	newline_flag;
	int	flag;
	int	i;

	newline_flag = 1;
	flag = 0;
	i = 0;
	if (lst->lexem[1] && lst->lexem[1][0] == '-' && lst->lexem[1][1] == 'n' \
		&& !lst->lexem[1][2])
	{
		newline_flag = 0;
		++i;
	}
	while (lst->lexem[++i])
	{
		while (lst->lexem[i] && !ft_strncmp(lst->lexem[i], "-n", 2) && !flag)
			++i;
		ft_putstr_fd(lst->lexem[i], 1);
		flag = 1;
		if (lst->lexem[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (newline_flag)
		ft_putstr_fd("\n", 1);
	mshell->exit_status = 0;
}

//handle 'cd'
//>no args / relative path / absolute path
//*relative path: homeD(~), currentD (./), parentD(../) & subdirectory (*/)
//*absolute path: full path starting w/ root
void	builtin_cd(t_minishell *mshell, t_list *lst)
{
	char	path[4096];

	if (lst->lexem[1] && ft_strncmp(lst->lexem[1], "~", 1))
	{
		if (lst->lexem[1][0] == '/')
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
				err_msg(mshell, 1, \
						"Minishell: cd: %s: No such file or directory\n", \
						lst->lexem[1]);
				return ;
			}
		}
	}
	else if (!lst->lexem[1] || !ft_strncmp(lst->lexem[1], "~", 1))
		chdir(ft_getenv(mshell, "HOME"));
	mshell->exit_status = 0;
}
//~: shortcut of $HOME, definitely is absolute path
//4096 is max path size state in limits.h

//handle 'env' (no arg)
//*show err msg if there argument passed in
void	builtin_env(t_minishell *mshell, t_list *lst)
{
	int	i;

	i = -1;
	if (lst->lexem[1])
	{
		err_msg(mshell, 127, \
				"env: '%s': No such file or directory\n", lst->lexem[1]);
		return ;
	}
	while (mshell->envp[++i])
	{
		if (ft_strchr(mshell->envp[i], '='))
			printf("%s\n", mshell->envp[i]);
	}
	mshell->exit_status = 0;
}
