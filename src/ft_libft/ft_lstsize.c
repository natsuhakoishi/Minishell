/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:53:03 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 01:02:34 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_lstsize(t_lst *lst)
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
