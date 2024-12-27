/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:07:39 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/27 12:29:24 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list)
	{
		if (list->next == NULL)
		{
			list->next = new;
			break ;
		}
		list = list->next;
	}
}
/*
#include <stdio.h>

int main(void)
{
	t_list	*list = NULL;
	t_list	*node1 = ft_lstnew("Maimai");
	t_list	*node2 = ft_lstnew("Chunithm");

	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	t_list	*cur = list;
	while (cur != NULL)
	{
		printf("Data：%s\n", (char *)cur->content);
		cur = cur->next;
	}
	free(node1);
	free(node2);
	return (0);
}
*/
