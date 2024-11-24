/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:53:21 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/25 02:07:16 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(t_minishell *mshell, char *evar)
{
	char	*value;
	char	*key;
	int		a;

	a = -1;
	value = NULL;
	if (!ft_strncmp(evar, "?\0". 2))
		return (ft_itoa(mshell->exit_status));
	while (mshell->envp[++a])
	{
		key = ft_substr(mshell->envp[a], 0,
				ft_strpos(mshell->envp[a], "="));
		if (!ft_strncmp(key, evar, ft_strlen(evar) + 1))
			value = ft_strchr(mshell->envp[a], '=') + 1;
		free(key);
	}
	return (value);
}

void	ft_free2(t_list *current)
{
	int	a;

	a = -1;
	while (current->args[++a])
		free(current->args[a]);
	free(current->args);
	if (current->infile)
		free(current->infile);
	if (current->outfile)
		free(current->outfile);
	if (current->delimiter)
		free(current->delimiter);
	free(current);
}

void	ft_free(t_minishell *mshell, t_list **lst)
{
	t_list	*next;
	t_list	*current;
	int		a;

	a = -1;
	if (mshell->input)
	{
		while (mshell->input[++a])
			free(mshell->input[a]);
		free(mshell->input);
	}
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_free2(current);
		current = next;
	}
	*lst = NULL;
}

void	exit_free(t_minishell *mshell, t_list **lst)
{
	ft_free(mshell, lst);
	free(lst);
	free(mshell);
	exit(mshell->exit_status);
}

//exit code? - exit_free
