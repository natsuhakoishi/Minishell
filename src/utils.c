/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:53:21 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/24 15:05:01 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free2(t_list *current)
{
	int	a;

	a = -1;
	while (current->args[++a])
		free(current->args[a]);
	free(current->args);
	if (current->infile)
		free(current->infile);
	if (current->outfile)
		free(current->outfile);
	if (current->delimiter)
		free(current->delimiter);
	free(current);
}

void	ft_free(t_minishell *mshell, t_list **lst)
{
	t_list	*next;
	t_list	*current;
	int		a;

	a = -1;
	if (mshell->input)
	{
		while (mshell->input[++a])
			free(mshell->input[a]);
		free(mshell->input);
	}
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_free2(current);
		current = next;
	}
	*lst = NULL;
}

void	exit_free(t_minishell *mshell, t_list **lst)
{
	ft_free(mshell, lst);
	free(lst);
	free(mshell);
	exit(mshell->exit_status);//exit code?
}