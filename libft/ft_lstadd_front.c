/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:37:45 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:18:10 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *(lst + 0);
	*(lst + 0) = new;
}
/*
#include <stdio.h>

int main(void)
{
	t_list	*list = NULL;
	t_list	*node1 = ft_lstnew("Maimai");
	t_list	*node2 = ft_lstnew("Chunithm");

	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
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
