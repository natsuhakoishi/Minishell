/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:30:05 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/05 02:47:32 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_list *current)
{
	int	a;

	a = -1;
	while (current->lexem[++a])
		free(current->lexem[a]);
	free(current->lexem);
	// if (current->in_path)
	// 	free(current->in_path);
	// if (current->out_path)
	// 	free(current->out_path);
	// if (current->delimiter)
	// 	free(current->delimiter);
	free(current);
}
//TODO: they malloc? lexem yes;

void	ft_free(t_minishell *mshell, t_list **lst)
{
	t_list	*next;
	t_list	*current;
	int		a;

	a = -1;
	if (mshell->token)
	{
		while (mshell->token[++a])
			free(mshell->token[a]);
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

void	exit_free(t_minishell *mshell, t_list **lst)
{
	ft_free(mshell, lst);
	free(lst);
	free(mshell);
	exit(mshell->exit_status);
}
