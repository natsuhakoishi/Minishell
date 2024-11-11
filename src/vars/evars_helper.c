/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evars_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:24:45 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 01:25:21 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	rebuild_envp(t_minishell *minish)
{
	int		a;
	int		lst_size;
	t_lst	*list;
	t_lst	*head;

	a = 0;
	list = minish->evars;
	lst_size = ft_lstsize(list);
	head = list;
	if (minish->my_envp != NULL)
		free_darr(&minish->my_envp);
	minish->my_envp = (char **)malloc(sizeof(char *) * (lst_size + 1));
	while (list != NULL)
	{
		minish->my_envp[a] = ft_strdup(list->env.str);
		a++;
		list = list->next;
	}
	minish->my_envp[a] = NULL;
	list = head;
}

t_lst	*set_env(char **envp)
{
	int		a;
	t_lst	*list;
	t_lst	*node;

	a = 0;
	list = NULL;
	while (envp[a] != NULL)
	{
		node = init_list(ft_strdup(envp[a]));
		ft_lstadd_back(&list, node);
		a++;
	}
	return (list);
}
