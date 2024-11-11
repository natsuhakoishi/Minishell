/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:41:26 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:20:01 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void	ft_pcontent(void *cont)
{
	printf("%s\n", (char *)cont);
}

int main(void)
{
	t_list	*list = NULL;
	t_list	*node1 = ft_lstnew("Maimai");
	t_list	*node2 = ft_lstnew("Chunithm");

	list = node1;
	node1->next = node2;
	ft_lstiter(list, ft_pcontent);
	free(node1);
	free(node2);
	return (0);
}
*/
