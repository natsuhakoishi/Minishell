/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:26:40 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/31 12:54:40 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !del || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = 0;
}
/*
#include <stdio.h>

void	ft_del(void *cont)
{
	free(cont);
}

int main(void)
{
	t_list	*list = NULL;
	t_list	*node1 = ft_lstnew("Maimai");
	t_list	*node2 = ft_lstnew("Chunithm");

	list = node1;
	node1->next = node2;
	ft_lstclear(&list, ft_del);
	t_list	*cur = list;
	while (cur != NULL)
	{
		printf("Data：%s\n", (char *)cur->content);
		cur = cur->next;
	}
	return (0);
}
*/
