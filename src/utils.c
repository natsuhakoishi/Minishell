/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:53:21 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/08 02:33:15 by zgoh             ###   ########.fr       */
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
	if (!ft_strncmp(evar, "?\0", 2))
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

int	check_built_in(t_list *lst)
{
	if (!lst->lexem[0])
		return (0);
	if (!ft_strncmp(lst->lexem[0], "pwd\0", 4))
		;
	else if (!ft_strncmp(lst->lexem[0], "exit\0", 5))
		;
	else if (!ft_strncmp(lst->lexem[0], "env\0", 4))
		;
	else if (!ft_strncmp(lst->lexem[0], "cd\0", 3))
		;
	else if (!ft_strncmp(lst->lexem[0], "echo\0", 5))
		;
	else if (!ft_strncmp(lst->lexem[0], "unset\0", 6))
		;
	else if (!ft_strncmp(lst->lexem[0], "export\0", 7))
		;
	else if (!ft_strncmp(lst->lexem[0], "./", 2) || \
				!ft_strncmp(lst->lexem[0], "/", 1))
		;
	else
		return (0);
	return (1);
}

char	*remove_quote(char	*s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != '\"' && s[i] != '\'')
			s[j++] = s[i];
	}
	s[j] = '\0';
	return (s);
}