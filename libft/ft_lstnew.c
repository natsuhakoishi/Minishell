/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:27:12 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/23 18:36:45 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void **command)
{
	//modified for minishell
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->args = command;
	node->append = 0;
	node->pipe_fd[0] = -1;
	node->pipe_fd[1] = -1;
	node->delimiter = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->next = NULL;
	return (node);
}
