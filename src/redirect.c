/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:05:48 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/30 07:18:42 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc2(t_minishell *mshell, t_list *lst, int fd, char *input)
{
	ft_signal(2);
	fd = open(".tmp", O_WRONLY | O_CREAT, 0644);
	input = readline(" > ");
	while (1)
	{
		if (!input)
		{
			ft_putstr_fd("Minishell: warning: here-document delimited by", 2);
			err_msg(mshell, 0, " end-of-file (wanted '%s')\n", lst->delimiter);
			break ;
		}
		if (!ft_strncmp(input, lst->delimiter, ft_strlen(lst->delimiter + 1)))
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
	exit (0);
}

void	here_doc(t_minishell *mshell, t_list *lst)
{
	pid_t	p_id;
	int		status;
	int		fd;
	char	*input;

	p_id = fork();
	input = NULL;
	fd = 0;
	if (p_id == 0)
		here_doc2(mshell, lst, fd, input);
	else if (p_id)
	{
		ft_signal(1);
		waitpid(p_id, &status, 0);
		status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && status == 42)
			mshell->here_doc = 1;
	}
}

void	redirect_setup2(t_list *lst, int i)
{
	int	status;

	status = check_if_redirect(lst, i);
	if (status == 1)
		lst->in_path = ft_strdup(lst->lexem[i + 1]);
	else if (status == 2 || status == 4)
		lst->out_path = ft_strdup(lst->lexem[i + 1]);
	else if (status == 3)
		lst->delimiter = ft_strdup(lst->lexem[i + 1]);
	if (lst->in_path || lst->out_path || lst->delimiter)
		lexem_update(&lst, i);
}

void	redirect_setup(t_list *lst, int i)
{
	int status;

	status = check_if_redirect(lst, i);
	if (status)
	{
		if (status == 1)
		{
			if (lst->in_path)
				free(lst->in_path);
		}
		else if (status == 2 || status == 4)
		{
			
			if (lst->out_path)
			{
				open(lst->out_path, O_WRONLY | O_CREAT, 0644);
				free(lst->out_path);
			}
			if (status == 4)
				lst->append = 1;
		}
		else if (status == 3)
		{
			if (lst->delimiter)
				free(lst->delimiter);
		}
	}
}

int	redirection(t_minishell *mshell, t_list *lst)
{
	t_list	*tmp;
	int		i;
	int		value;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (tmp->lexem && tmp->lexem[i])
		{
			value = redirect_syntax(mshell, tmp, i);
			if (!value)
				return (0);
			else if (value == 1)
			{
				redirect_setup(tmp, i);
				redirect_setup2(tmp, i);
				++i;
			}
			++i;
		}
		tmp = tmp->next;
	}
	return (1);
}
