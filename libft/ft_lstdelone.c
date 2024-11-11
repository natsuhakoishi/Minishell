/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:15:36 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 19:28:03 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}
/*
#include <stdio.h>

void	ft_del(void *cont)
{
	free(cont);
}

int main(void)
{
	t_list	*node1 = ft_lstnew(ft_strdup("Maimai"));

	ft_lstdelone(node1, ft_del);
	printf("%s\n", (char *)node1->content);
	return (0);
}
*/
