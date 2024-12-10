/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:05:48 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/10 15:22:04 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_setup(t_minishell *mshell, t_list *lst, int i)
{
	int	fd;

	fd = 0;
	(void)mshell;
	if (!ft_strncmp(lst->lexem[i], ">\0", 2))
	{
		lst->out_path = lst->lexem[i + 1];
		// fd = open(lst->out_path, O_CREAT, 0777);
		// close(fd);
	}
	else if (!ft_strncmp(lst->lexem[i], "<\0", 2))
		lst->in_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], ">>\0", 3))
	{
		lst->append = 1;
		lst->out_path = lst->lexem[i + 1];
		// fd = open(lst->out_path, O_CREAT, 0777);
		// close(fd);
	}
	else if (!ft_strncmp(lst->lexem[i], "<<\0", 3))
		lst->delimiter = lst->lexem[i + 1];
}
//todo: file creating might redundant

int	check_redirect_syntax(t_minishell *mshell, t_list *lst, int i)
{
	char	*current;
	char	*next;

	current = lst->lexem[i];
	next = lst->lexem[i + 1];
	if ((!ft_strncmp(current, ">\0", 2)) || (!ft_strncmp(current, "<\0", 2)) || \
		(!ft_strncmp(current, ">>\0", 3)) || (!ft_strncmp(current, "<<\0", 3)))
	{
		if ((!ft_strncmp(next, ">\0", 2)) || (!ft_strncmp(next, "<\0", 2)) || \
			(!ft_strncmp(next, ">>\0", 3)) || (!ft_strncmp(next, "<<\0", 3)))
		{
			perror("Minishell: syntax error at redirection\n");
			mshell->exit_status = -1;
			return (0);
		}
	}
	return (1);
}

int	redirection(t_minishell *mshell, t_list *lst)
{
	int		i;

	while (lst && lst->lexem)
	{
		i = -1;
		while (lst->lexem[++i])
		{
			if (!check_redirect_syntax(mshell, lst, i))
				return (0);
			redirect_setup(mshell, lst, i);
		}
		lst = lst->next;
	}
	return (1);
}
//didn't purposely take off redirection and its argumnet from linked list
//TODO file permission (set properly), 
//TODO remove redirection related from node, better for following step