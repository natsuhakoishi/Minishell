/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa <yyean-wa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:53:22 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/08/02 22:49:32 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;

	if (!lst || !f || !del)
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (0);
	node = new_list;
	lst = lst->next;
	while (lst)
	{
		node->next = ft_lstnew(f(lst->content));
		if (!node->next)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		node = node->next;
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>
#include <string.h>

void	ft_del(void *cont)
{
	free(cont);
}

void	*ft_mark(void *cont)
{
	char	*mark = malloc(strlen(cont) + strlen("
	  - if u see this, f added" + 1));
	strcpy(mark, cont);
	strcat(mark, " - if u see this, f added");
	return (mark);
}

int	main(void)
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew("Maimai"));
	ft_lstadd_back(&list, ft_lstnew("Chunithm"));
	ft_lstadd_back(&list, ft_lstnew("Ongeki"));

	t_list	*added_list = ft_lstmap(list, &ft_mark, &ft_del);
	t_list	*cur = added_list;
	while (cur)
	{
		printf("%s\n", (char *)cur->content);
		cur = cur->next;
	}
	return (0);
}
*/
