/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:35:43 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/10 16:08:37 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fork a child process for each node
//each child process will need handle one commmand with its option/flag
void	childs_management(t_minishell *mshell, t_list *lst, pid_t *childs)
{
	int	i;

	i = -1;
	while (lst)
	{
		if (lst->delimiter != NULL)
			here_doc(mshell, lst);
		childs[++i] = fork();
		if (childs[i] == 0)
			child_process(mshell, lst);
		else
		{
			close(lst->pipe_fd[0]);
			if (lst->next)
				close(lst->pipe_fd[1]);
			lst = lst->next;
		}
	}
}

void	execution(t_minishell *mshell, t_list *lst)
{
	t_list	*head;
	pid_t	*childs;

	head = lst;
	childs = malloc(ft_lstsize(lst) * sizeof(pid_t));
	init_pipe(mshell);
	ft_signal(1);
	if (!lst->next && check_built_in(lst)) //code optimization&foster execution
		built_in(mshell, lst);
	else
	{
		childs_management(mshell, lst, childs);
		dup2(mshell->in_backup, 0);
		dup2(mshell->out_backup, 1);
		close(mshell->in_backup);
		close(mshell->out_backup);
	}
	lst = head;
	free(childs);
}
//how bash execute a command:
//	built-in? :run; :exist in $PATH? : fork child process & run; error;