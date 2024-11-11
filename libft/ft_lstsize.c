/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:53:03 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:25:01 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	a;

	a = 0;
	while (lst)
	{
		a++;
		lst = lst->next;
	}
	return (a);
}
/*
#include <stdio.h>

int main(void)
{
	t_list	*list = NULL;
	t_list	*node1 = ft_lstnew("Maimai");
	t_list	*node2 = ft_lstnew("Chunithm");
	int		size;

	list = node1;
	node1->next = node2;
	size = ft_lstsize(list);
	printf("Size: %d\n", size);
	free(node1);
	free(node2);
	return (0);
}
*/
