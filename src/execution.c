/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:35:43 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/16 07:17:56 by zgoh             ###   ########.fr       */
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
		if (lst->next)
			pipe(lst->next->pipe_fd);
		if (lst->delimiter != NULL)
			here_doc(mshell, lst);
		childs[++i] = fork();
		if (childs[i] == 0)
			child_process(mshell, lst);
		else
		{
			close(lst->pipe_fd[0]);
			if (lst->next)
				close(lst->next->pipe_fd[1]);
			lst = lst->next;
		}
	}
	i = -1;
	while (childs[++i])
	{
		waitpid(childs[i], &mshell->exit_status, 0);
		mshell->exit_status = mshell->exit_status % 256;
	}
}

void	built_in(t_minishell *mshell, t_list *lst)
{
	if (lst->lexem[0] == NULL)
		return ;
	if (!ft_strncmp(lst->lexem[0], "pwd", 3))
	{
		printf("%s\n", mshell->cwd);
		mshell->exit_status = 0;
	}
	else if (!ft_strncmp(lst->lexem[0], "exit", 4))
		builtin_exit(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "env", 3))
		builtin_env(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "cd", 2))
		builtin_cd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "echo", 4))
		builtin_echo(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "unset", 5))
		builtin_unset(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "export", 6))
		builtin_export(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
			!ft_strncmp(lst->lexem[0], "/", 1))
		executable(mshell, lst);
}

void	execution(t_minishell *mshell, t_list *lst)
{
	pid_t	*childs;

	// printf("start execution\n");
	mshell->in_backup = dup(0);
	mshell->out_backup = dup(1);
	mshell->in_fd = 0;
	mshell->out_fd = 1;
	childs = malloc(ft_lstsize(lst) * sizeof(pid_t));
	ft_signal(1);
	// for (int j = 0; lst->lexem && lst->lexem[j]; ++j)
	// 	printf("(%d %s\t)", j, lst->lexem[j]);
	// printf(".\nbefore execution fak uuuu\n");
	if (lst->next == NULL && check_built_in(lst))
		built_in(mshell, lst);
	else
	{
		childs_management(mshell, lst, childs);
		dup2(mshell->in_backup, 0);
		dup2(mshell->out_backup, 1);
		close(mshell->in_backup);
		close(mshell->out_backup);
	}
	unlink(".tmp");
	free(childs);
}
//number of child = number of node = number of cmd
