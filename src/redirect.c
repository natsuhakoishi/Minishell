/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:05:48 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/25 19:49:48 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_minishell *mshell, t_list *lst)
{
	int		fd;
	pid_t	p_id;
	char	*input;

	p_id = fork();
	input = NULL;
	if (p_id == 0)
	{
		fd = open(".tmp", O_WRONLY | O_CREAT, 0644);
		input = readline(" > ");
		if (!input)
		{
			ft_putstr_fd("Minishell: warning: here-document delimited by", 2);
			err_msg(mshell, 0 , " end-of-file (wanted '%s')\n", lst->delimiter);
			return ;
		}
		while (input != NULL && ft_strncmp(input, lst->delimiter, ft_strlen(lst->delimiter + 1)))
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
			input = readline(" > ");
		}
		free(input);
		close(fd);
		exit (0);
	}
	else if (p_id)
		waitpid(p_id, NULL, 0);
}
//todo set proper exit status betw. parent & child

void	redirect_setup(t_list *lst, int i)
{
	if (!ft_strncmp(lst->lexem[i], "<\0", 2))
		lst->in_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], ">\0", 2))
		lst->out_path = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], "<<\0", 3))
		lst->delimiter = lst->lexem[i + 1];
	else if (!ft_strncmp(lst->lexem[i], ">>\0", 3))
	{
		lst->append = 1;
		lst->out_path = lst->lexem[i + 1];
	}
	if (lst->in_path || lst->out_path || lst->append || lst->delimiter)
		lexem_update(lst, i);
}

int	redirect_syntax(t_minishell *mshell, t_list *lst, int i)
{
	char	*current;
	char	*next;

	if (!lst->lexem)
		return (0);
	current = lst->lexem[i];
	next = lst->lexem[i + 1];
	if ((!ft_strncmp(current, ">\0", 2)) || (!ft_strncmp(current, "<\0", 2)) || \
		(!ft_strncmp(current, ">>\0", 3)) || (!ft_strncmp(current, "<<\0", 3)))
	{
		if (next == NULL || (next && \
			((!ft_strncmp(next, ">\0", 2)) || (!ft_strncmp(next, "<\0", 2)) || \
			(!ft_strncmp(next, ">>\0", 3)) || (!ft_strncmp(next, "<<\0", 3)))))
		{
			err_msg(mshell, 2, "Error: syntax near redirection.\n", NULL);
			return (0);
		}
		return (1);
	}
	return (2);
}

int	redirection(t_minishell *mshell, t_list *lst)
{
	int		i;
	int		value;

	while (lst && lst->lexem)
	{
		i = -1;
		while (lst->lexem[++i])
		{
			value = redirect_syntax(mshell, lst, i);
			if (!value)
				return (0);
			else if (value == 1)
			{
				redirect_setup(lst, i);
				--i;
			}
		}
		lst = lst->next;
	}
	return (1);
}
