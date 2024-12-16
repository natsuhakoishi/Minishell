/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:30:05 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/16 23:01:57 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_list *current)
{
	if (!current || !current->lexem)
		return ;
	free_dptr(current->lexem);
	current = NULL;
}
//in_path, out_path & delimiter no need free because they no dynamically assigned memory

void	ft_free(t_minishell *mshell, t_list **lst)
{
	t_list	*next;
	t_list	*current;

	if (lst && *lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			free_node(current);
			current = next;
		}
		*lst = NULL;
	}
	if (mshell && mshell->token)
		free_dptr(mshell->token);
}

void	free_exit(t_minishell *mshell, t_list **lst)
{
	int	code;

	code = mshell->exit_status;
	if (mshell || (lst && *lst))
	{
		ft_free(mshell, lst);
		// free(mshell);
		// free(lst);
	}
	exit(code);
}

void	free_dptr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}
