/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:05:48 by zgoh              #+#    #+#             */
/*   Updated: 2024/11/30 03:37:51 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_redirect(t_minishell *mshell, t_list *lst, int i)
{
	if (!ft_strncmp(lst->lexem[i], ">\0", 2))
		lst->out_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], "<\0", 2))
		lst->in_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], ">>\0", 3))
		//
	else if (!ft_strncmp(lst->lexem[i], "<<\0", 3))
		//
}

int	check_redirect(t_minishell *mshell, t_list *lst, int i)
{
	char	*current;
	char	*next;

	current = lst->lexem[i];
	next = lst->lexem[i + 1];
	if ((!ft_strncmp(current, ">\0", 2)) || (!ft_strncmp(current, "<\0", 2)) || \
		(!ft_strncmp(current, ">>\0", 3)) || (!ft_strncmp(current, "<<\0", 3)))
	{
		if ((!ft_strncmp(next, ">\0", 2)) || (!ft_strncmp(next, "<\0", 2)) || \
			(!ft_strncmp(next, ">>\0", 3)) || (!ft_strncmp(next, "<<\0", 3)))
		{
			//print error message about syntax
			return (0);
		}
	}
	return (1);
}

void	the_redirec(t_minishell *mshell, t_list **lst_sp)
{
	t_list	*lst;
	int		i;

	lst = *lst_sp;
	while (lst && lst->lexem)
	{
		i = -1;
		while (lst->lexem[++i])
		{
			if (!check_redirect(mshell, lst, i))
				//not passed redirect syntax check
			choose_redirect(mshell, lst, i);
		}
		lst = lst->next;
	}
}
