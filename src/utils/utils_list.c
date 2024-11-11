/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:33:48 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 00:38:03 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lst	*init_list(char *new)
{
	t_lst	*list;

	list = (t_lst *)malloc(sizeof(t_lst));
	list->env.str = new;
	list->env.printed = 0;
	list->cmd.cmd = NULL;
	list->next = NULL;
	list->fd_in = -1;
	list->fd_out = -1;
	return (list);
}
