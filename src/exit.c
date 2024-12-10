/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:30:05 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/10 23:48:13 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_list *current)
{
	int	a;

	if (!current)
		return ;
	if (current->lexem)
	{
		a = 0;
		while (current->lexem[a])
		{
			free(current->lexem[a]);
			a++;
		}
		free(current->lexem);
	}
	if (current->in_path)
		free(current->in_path);
	if (current->out_path)
		free(current->out_path);
	if (current->delimiter)
		free(current->delimiter);
	free(current);
}
//TODO: they malloc? lexem yes;

void	ft_free(t_minishell *mshell, t_list **lst)
{
	t_list	*next;
	t_list	*current;
	int		a;

	if (lst && *lst)
		ft_lstclear(lst, free);
	if (mshell->token)
	{
		a = 0;
		while (mshell->token[a])
			free(mshell->token[a++]);
		free(mshell->token);
	}
	current = *lst;
	while (current) //free the linked list
	{
		next = current->next;
		free_node(current);
		current = next;
	}
	*lst = NULL;
}

void	free_exit(t_minishell *mshell, t_list **lst)
{
	int	code;

	code = mshell->exit_status;
	ft_free(mshell, lst);
	free(lst);
	free(mshell);
	exit(code);
}
