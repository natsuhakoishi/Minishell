/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:53:21 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/31 10:16:17 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(t_minishell *mshell, char *evar)
{
	char	*value;
	int		a;

	a = -1;
	value = NULL;
	if (!ft_strncmp(evar, "?\0", 2))
		return (ft_itoa(mshell->exit_status));
	while (mshell->envp[++a])
	{
		if (!ft_strncmp(mshell->envp[a], evar, ft_strlen(evar)) && \
			mshell->envp[a][ft_strlen(evar)] == '=')
		{
			value = ft_strchr(mshell->envp[a], '=') + 1;
			break ;
		}
	}
	if (!value)
		return ("");
	return (value);
}

void	envp_sorting(char **envp, int size)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < (size - 1) - i)
		{
			if (ft_strncmp(envp[j], envp[j + 1], BUFFER) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
		}
	}
}

void	lexem_update(t_list **lst, int i)
{
	t_list	*tmp;

	free((*lst)->lexem[i]);
	free((*lst)->lexem[i + 1]);
	while ((*lst)->lexem[i + 2])
	{
		(*lst)->lexem[i] = (*lst)->lexem[i + 2];
		++i;
	}
	(*lst)->lexem[i] = NULL;
	if ((*lst)->lexem == NULL)
	{
		tmp = (*lst)->next;
		free_dptr((*lst)->lexem);
		free(*lst);
		*lst = tmp;
	}
}

void	kindergarden_end(pid_t *childs, t_minishell *mshell)
{
	int	status;
	int	i;

	i = -1;
	while (childs[++i] != -1)
	{
		waitpid(childs[i], &status, 0);
		if (WIFSIGNALED(status))
			mshell->exit_status = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			mshell->exit_status = status;
		}
	}
}

// void	print_node(t_list *lst)
// {
// 	t_list *temp;
// 	int	j;
// 	j = 0;
// 	if (!lst)
// 		printf("empty list ha\n");
// 	temp = lst;
// 	while (temp)
// 	{
// 		printf("node %dth\n", j);
// 		++j;
// 		if (temp->lexem != NULL)
// 		{
// 			printf("\t");
// 			for (int a = 0; temp->lexem[a]; ++a)
// 				printf("\t%s", temp->lexem[a]);
// 			printf("\t(null)");
// 			printf("\n");
// 		}
// 		else
// 			printf("\tno content\n");
// 		temp = temp->next;
// 	}
// }
