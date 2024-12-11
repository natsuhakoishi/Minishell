/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:12:01 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/11 02:25:59 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_pipe(t_minishell *mshell)
// {
// 	mshell->in_backup = dup(0);
// 	mshell->out_backup = dup(1);
// 	mshell->in_fd = 0;
// 	mshell->out_fd = 1;
// }

void	input_setup(t_minishell *mshell, t_list *lst)
{
	if (lst->in_path)
		mshell->in_fd = open(lst->in_path, O_RDONLY);
	else if (lst->delimiter)
		mshell->in_fd = open(".tmp", O_RDONLY);
	else if (lst->pipe_fd[0] != -1 && lst->pipe_fd[0] != 0)
		mshell->in_fd = lst->pipe_fd[0];
	else
		mshell->in_fd = dup(mshell->in_backup);
	if (mshell->in_fd == -1)
	{
		perror("Minishell: can't open file\n");
		lst->in_path = NULL;
		exit(-1);
	}
	if (dup2(mshell->in_fd, 0) == -1)
	{
		perror("dup2: in fd\n");
		return ;
	}
	close(mshell->in_fd);
}

void	output_setup(t_minishell *mshell, t_list *lst)
{
	if (lst->out_path && !(lst->append))
		mshell->out_fd = open(lst->out_path, O_WRONLY | O_CREAT | O_TRUNC, \
			0777);
	else if (lst->out_path && lst->append)
		mshell->out_fd = open(lst->out_path, O_WRONLY | O_CREAT | O_APPEND, \
			0777);
	else if (lst->next)
	{
		mshell->out_fd = lst->next->pipe_fd[1];
		close(lst->next->pipe_fd[0]);
	}
	else
		mshell->out_fd = dup(mshell->out_backup);
	if (dup2(mshell->out_fd, 1) == -1)
	{
		perror("dup2: out fd\n");
		return ;
	}
	close(mshell->out_fd);
}
