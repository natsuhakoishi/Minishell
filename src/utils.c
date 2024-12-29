/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:53:21 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/30 07:31:39 by zgoh             ###   ########.fr       */
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

int	check_built_in(t_list *lst)
{
	if (!lst || !lst->lexem || !lst->lexem[0])
		return (0);
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		return (1);
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
			!ft_strncmp(lst->lexem[0], "/", 1))
		return (1);
	return (0);
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

	// printf("%p\n", (*lst)->lexem[i]);
	free((*lst)->lexem[i]);
	free((*lst)->lexem[i + 1]);
	while ((*lst)->lexem[i + 2])
	{
		// printf("hello\n");
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
//todo deal with empty node after update

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

int	check_if_redirect(t_list *lst, int i)
{
	if (!ft_strncmp(lst->lexem[i], "<\0", 2))
		return (1);
	else if (!ft_strncmp(lst->lexem[i], ">\0", 2))
		return (2);
	else if (!ft_strncmp(lst->lexem[i], "<<\0", 3))
		return (3);
	else if (!ft_strncmp(lst->lexem[i], ">>\0", 3))
		return (4);
	else
		return (0);
}


int	redirect_syntax(t_minishell *mshell, t_list *lst, int i)
{
	if (!lst->lexem || !(*lst->lexem))
		return (0);
	if (check_if_redirect(lst, i))
	{
		if (!lst->lexem[i + 1] || check_if_redirect(lst, i + 1))
		{
			err_msg(mshell, 2, "Syntax error near redirection.\n", NULL);
			return (0);
		}
		return (1);
	}
	return (2);
}
