/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:21:44 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/31 07:28:01 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(t_minishell *mshell, int exit_status, char *msg, char *arg)
{
	int	i;

	i = -1;
	while (msg[++i])
	{
		if (msg[i] == '%' && msg[i + 1] == 's' && arg)
		{
			ft_putstr_fd(arg, 2);
			++i;
			continue ;
		}
		ft_putchar_fd(msg[i], 2);
	}
	mshell->exit_status = exit_status;
}

int	check_if_redirect(t_list *lst, int i)
{
	if (!ft_strncmp(lst->lexem[i], "<\0", 2))
		return (1);
	else if (!ft_strncmp(lst->lexem[i], ">\0", 2))
		return (2);
	else if (!ft_strncmp(lst->lexem[i], "<<\0", 3))
		return (3);
	else if (!ft_strncmp(lst->lexem[i], ">>\0", 3))
		return (4);
	else
		return (0);
}

int	check_redirect_syntax(t_minishell *mshell, t_list *lst, int i)
{
	if (!lst->lexem || !(*lst->lexem))
		return (0);
	if (check_if_redirect(lst, i))
	{
		if (!lst->lexem[i + 1] || check_if_redirect(lst, i + 1))
		{
			err_msg(mshell, 2, "Syntax error near redirection.\n", NULL);
			return (0);
		}
		return (1);
	}
	return (2);
}

int	check_built_in(t_list *lst)
{
	if (!lst || !lst->lexem || !lst->lexem[0])
		return (0);
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
			!ft_strncmp(lst->lexem[0], "/", 1))
		return (1);
	return (0);
}
