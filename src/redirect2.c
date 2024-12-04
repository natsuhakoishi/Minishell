/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:13:15 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/05 02:44:29 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_heredoc(t_minishell *mshell)
{
	mshell->in_fd = dup(mshell->in_backup);
	dup2(mshell->in_fd, 0);
	close(mshell->in_fd);
	mshell->out_fd = dup(mshell->out_backup);
	dup2(mshell->out_fd, 1);
	close(mshell->out_fd);
}

//mimic behaviour of here doc
//basically a scanf but need keyword to stop it
void	here_doc(t_minishell *mshell, t_list *lst)
{
	int		fd;
	char	*input;

	ft_signal(0);
	pre_heredoc(mshell);
	fd = open(".tmp", O_WRONLY | O_CREAT, 0777);
	input = readline(" > ");
	while (input != NULL)
	{
		ft_signal(2);
		if (!(ft_strncmp(input, lst->delimiter, \
			ft_strlen(lst->delimiter + 1))))
		{
			free(input);
			break ;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline(" > ");
	}
	close(fd);
}
//todo free twice?