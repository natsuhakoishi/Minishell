/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:27:12 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:21:19 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*node1 = ft_lstnew("Maimai");
	t_list	*node2 = ft_lstnew("Chunithm");

	printf("node1：%s\n", (char *)node1->content);
	printf("node2：%s\n", (char *)node2->content);
	node1->next = node2;
	printf("Chain：%s -> %s\n", (char *)node1->content, (char *)node2->content);
	free(node1);
	free(node2);
	return (0);
}
*/
