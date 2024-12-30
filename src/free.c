/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:30:05 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/30 09:18:07 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	free_lst(t_minishell *mshell, t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp_next;

	if (!mshell->flag || !lst || !(*lst))
		return ;
	tmp = *lst;
	tmp_next = NULL;
	while (tmp)
	{
		tmp_next = tmp->next;
		free_dptr(tmp->lexem);
		if (tmp->in_path)
			free(tmp->in_path);
		if (tmp->out_path)
			free(tmp->out_path);
		if (tmp->delimiter)
			free(tmp->delimiter);
		free(tmp);
		tmp = tmp_next;
	}
	*lst = tmp;
	*lst = NULL;
	if (mshell->flag)
		mshell->flag = 0;
}

void	err_msg(t_minishell *mshell, int exit_status, char *msg, char *arg)
{
	int	i;

	i = -1;
	while (msg[++i])
	{
		if (msg[i] == '%' && msg[i + 1] == 's' && arg)
		{
			ft_putstr_fd(arg, 2);
			++i;
			continue ;
		}
		ft_putchar_fd(msg[i], 2);
	}
	mshell->exit_status = exit_status;
}
