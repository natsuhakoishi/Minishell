/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:05:48 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/16 07:17:23 by zgoh             ###   ########.fr       */
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

void	redirect_setup(t_minishell *mshell, t_list *lst, int i)
{
	// int	fd;

	// fd = 0;
	(void)mshell;
	if (!ft_strncmp(lst->lexem[i], ">", 1))
	{
		lst->out_path = lst->lexem[i + 1];
		// fd = open(lst->out_path, O_CREAT, 0777);
		// close(fd);
	}
	else if (!ft_strncmp(lst->lexem[i], "<", 1))
		lst->in_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], ">>", 2))
	{
		lst->append = 1;
		lst->out_path = lst->lexem[i + 1];
		// fd = open(lst->out_path, O_CREAT, 0777);
		// close(fd);
	}
	else if (!ft_strncmp(lst->lexem[i], "<<", 2))
		lst->delimiter = lst->lexem[i + 1];
	if (!ft_strncmp(lst->lexem[i], ">", 1) || \
		!ft_strncmp(lst->lexem[i], "<", 1) || !ft_strncmp( \
		lst->lexem[i], ">>", 2) || !ft_strncmp(lst->lexem[i], "<<", 2))
		arg_update(lst, i);
}
//todo: file creating might redundant

//check if consecutive redirect symbol
//todo check args after redirect symbol is exist
int	check_redirect_syntax(t_minishell *mshell, t_list *lst, int i)
{
	char	*current;
	char	*next;

	current = lst->lexem[i];
	next = lst->lexem[i + 1];
	if ((!ft_strncmp(current, ">\0", 2)) || (!ft_strncmp(current, "<\0", 2)) || \
		(!ft_strncmp(current, ">>\0", 3)) || (!ft_strncmp(current, "<<\0", 3)))
	{
		if (next && (\
			(!ft_strncmp(next, ">\0", 2)) || (!ft_strncmp(next, "<\0", 2)) || \
			(!ft_strncmp(next, ">>\0", 3)) || (!ft_strncmp(next, "<<\0", 3))))
		{
			perror("Minishell: syntax error at redirection\n");
			mshell->exit_status = -1;
			return (0);
		}
		return (1);
	}
	return (2);
}
//fix next args is null then segfault; better checking

int	redirection(t_minishell *mshell, t_list *lst)
{
	int		i;
	int		value;

	while (lst && lst->lexem)
	{
		i = -1;
		while (lst->lexem[++i])
		{
			value = check_redirect_syntax(mshell, lst, i);
			if (!value)
				return (0);
			else if (value == 1)
				redirect_setup(mshell, lst, i);
		}
		// for (int j = 0; lst->lexem[j]; ++j)
		// 	printf("%s\t", lst->lexem[j]);
		lst = lst->next;
	}
	return (1);
}
//didn't purposely take off redirection and its argumnet from linked list
//TODO file permission (set properly)
