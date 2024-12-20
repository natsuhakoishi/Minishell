/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:35:43 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/21 03:34:49 by zgoh             ###   ########.fr       */
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
//each child process will need handle one commmand with its option/flag
void	childs_management(t_minishell *mshell, t_list *lst, pid_t *childs)
{
	int	i;

	i = -1;
	// printf("start kindergarden\n"); //Debug
	if (pipe(lst->pipe_fd) == -1)
	{
		ft_putstr_fd("Pipe setup fail\n", 2);
	}
	while (lst)
	{
		if (lst->next != NULL)
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
		mshell->exit_status %= 256;
	}
}

void	execution(t_minishell *mshell, t_list *lst)
{
	pid_t	*childs;

	// printf("start execution\n"); //Debug
	mshell->in_backup = dup(0);
	mshell->out_backup = dup(1);
	mshell->in_fd = 0;
	mshell->out_fd = 1;
	// printf("total child: %d\n", ft_lstsize(lst)); //Debug
	// print_node(lst); //Debug
	childs = malloc(ft_lstsize(lst) * sizeof(pid_t));
	ft_signal(1);
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
//memo if didnt do built-in only, all redirection worked with builtin