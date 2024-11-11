/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:07:39 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 01:02:49 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*list;

	list = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
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
