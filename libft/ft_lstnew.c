/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:27:12 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/21 03:39:44 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **command)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->lexem = command;
	node->append = 0;
	node->delimiter = NULL;
	node->in_path = NULL;
	node->out_path = NULL;
	node->pipe_fd[0] = -1;
	node->pipe_fd[1] = -1;
	node->next = NULL;
	return (node);
}
//modified for minishell
//lst-function in-used: lstnew, lstsize, lst_addback