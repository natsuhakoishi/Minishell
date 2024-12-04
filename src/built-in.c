/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:38:23 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/05 02:43:29 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pwd
//echo
//exit
//unset
//env
//cd
//export
//run

void	built_in(t_minishell *mshell, t_list *lst)
{
	if (lst->lexem[0] == NULL)
		return ;
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
		builtin_echo(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		builtin_pwd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		builtin_export(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		builtin_unset(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		builtin_env(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		builtin_cd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		builtin_exit(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
				!ft_strncmp(lst->lexem[0], "/", 1))
		builtin_run(mshell, lst);
}
//beware the in & out fd
