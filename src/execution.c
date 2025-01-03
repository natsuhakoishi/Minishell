/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:35:43 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/31 08:04:03 by zgoh             ###   ########.fr       */
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
void	kindergarden(t_minishell *mshell, t_list *lst, pid_t *childs)
{
	int	i;

	i = -1;
	while (lst)
	{
		if (lst->next)
			pipe(lst->next->pipe_fd);
		if (lst->delimiter)
			here_doc(mshell, lst);
		childs[++i] = fork();
		if (childs[i] == 0)
		{
			ft_signal(1);
			child_process(mshell, lst);
		}
		else
		{
			if (lst->pipe_fd[0] != -1)
				close(lst->pipe_fd[0]);
			if (lst->next)
				close(lst->next->pipe_fd[1]);
			lst = lst->next;
		}
	}
	kindergarden_end(childs, mshell);
}

void	only_built_in(t_minishell *mshell, t_list *lst)
{
	int	status;

	status = input_setup(mshell, lst);
	if (status)
		return ;
	if (mshell->here_doc)
		return ;
	output_setup(mshell, lst);
	built_in(mshell, lst);
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

	if (!lst || !lst->lexem)
		return ;
	exec_fd_setup(mshell);
	childs = malloc((ft_lstsize(lst) + 1) * sizeof(pid_t));
	if (!childs)
		return ;
	childs[ft_lstsize(lst)] = -1;
	ft_signal(1);
	if (lst->next == NULL && check_built_in(lst))
		only_built_in(mshell, lst);
	else
		kindergarden(mshell, lst, childs);
	dup2(mshell->in_backup, 0);
	dup2(mshell->out_backup, 1);
	close(mshell->in_backup);
	close(mshell->out_backup);
	unlink(".tmp");
	free(childs);
}
