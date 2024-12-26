/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:35:43 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/26 20:00:45 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in(t_minishell *mshell, t_list *lst)
{
	if (lst->lexem[0] == NULL)
		return ;
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
	{
		printf("%s\n", mshell->cwd);
		mshell->exit_status = 0;
	}
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		builtin_exit(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		builtin_env(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		builtin_cd(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		builtin_echo(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		builtin_unset(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		builtin_export(mshell, lst);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
			!ft_strncmp(lst->lexem[0], "/", 1))
		executable(mshell, lst);
}

//fork a child process for each node
//each child process handle one commmand(including option & arguments)
void	kindergarden(t_minishell *mshell, t_list *lst, pid_t *childs, int i)
{
	while (lst)
	{
		if (lst->next)
			pipe(lst->next->pipe_fd);
		if (lst->delimiter)
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
	while (childs[++i] != -1)
	{
		waitpid(childs[i], &mshell->exit_status, 0);
		mshell->exit_status = WEXITSTATUS(mshell->exit_status);
	}
}

void	exec_fd_setup(t_minishell *mshell)
{
	mshell->in_backup = dup(0);
	mshell->out_backup = dup(1);
	mshell->in_fd = 0;
	mshell->out_fd = 1;
}

void	execution(t_minishell *mshell, t_list *lst)
{
	pid_t	*childs;
	int		i;

	i = -1;
	if (!lst || !lst->lexem)
		return ;
	exec_fd_setup(mshell);
	childs = malloc((ft_lstsize(lst) + 1) * sizeof(pid_t));
	if (!childs)
		return ;
	childs[ft_lstsize(lst)] = -1;
	ft_signal(1);
	if (lst->next == NULL && check_built_in(lst))
	{
		input_setup(mshell, lst);
		if (mshell->here_doc)
			return ;
		output_setup(mshell, lst);
		built_in(mshell, lst);
	}
	else
		kindergarden(mshell, lst, childs, i);
	dup2(mshell->in_backup, 0);
	dup2(mshell->out_backup, 1);
	close(mshell->in_backup);
	close(mshell->out_backup);
	unlink(".tmp");
	free(childs);
}
