/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:05:48 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/02 15:11:22 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_setup(t_minishell *mshell, t_list *lst, int i)
{
	int	temp;

	temp = 0;
	if (!ft_strncmp(lst->lexem[i], ">\0", 2))
	{
		lst->out_path = lst->lexem[i + 1];
		temp = open(lst->out_path, O_CREAT, 0777);
		close(temp);
	}
	else if (!ft_strncmp(lst->lexem[i], "<\0", 2))
		lst->in_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], ">>\0", 3))
	{
		lst->append = 1;
		lst->out_path = lst->lexem[i + 1];
		temp = open(lst->out_path, O_CREAT, 0777);
		close(temp);
	}
	else if (!ft_strncmp(lst->lexem[i], "<<\0", 3))
		lst->delimiter = lst->lexem[i + 1];
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
			//print error message for redirection syntax
			mshell->exit_status = -1;
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
			redirect_setup(mshell, lst, i);
		}
		lst = lst->next;
	}
}
