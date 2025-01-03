/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:55:19 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/21 19:03:53 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_others(t_minishell *mshell, char *temp, char *result, int i[3])
{
	char	*envtmp;

	if (mshell->token[i[0]][i[1]] == '\"')
	{
		if (mshell->quote == 0)
			mshell->quote = 1;
		else
			mshell->quote = 0;
	}
	else if (mshell->token[i[0]][i[1]] == '~')
	{
		temp[++i[2]] = mshell->token[i[0]][i[1]];
		temp[++i[2]] = '\0';
		envtmp = ft_getenv(mshell, "HOME");
		ft_strlcat(result, envtmp, ft_strlen(result) + ft_strlen(envtmp) + 1);
	}
	else
	{
		temp[++i[2]] = mshell->token[i[0]][i[1]];
		temp[++i[2]] = '\0';
		ft_strlcat(result, temp, ft_strlen(result) + ft_strlen(temp) + 1);
	}
}

void	handle_expand(t_minishell *mshell, char *temp, char *result, int i[3])
{
	char	*envtmp;

	if (mshell->token[i[0]][i[1] + 1] == '?')
	{
		temp[++i[2]] = mshell->token[i[0]][++i[1]];
		temp[++i[2]] = '\0';
		envtmp = ft_itoa(mshell->exit_status);
		ft_strlcat(result, envtmp, ft_strlen(result) + ft_strlen(envtmp) + 1);
		free(envtmp);
	}
	else
	{
		while (mshell->token[i[0]][++i[1]] &&
				(ft_isalnum(mshell->token[i[0]][i[1]]) || \
				mshell->token[i[0]][i[1]] == '_'))
			temp[++i[2]] = mshell->token[i[0]][i[1]];
		i[1]--;
		temp[++i[2]] = '\0';
		if (ft_getenv(mshell, temp))
			ft_strlcat(result, ft_getenv(mshell, temp),
				ft_strlen(result) + ft_strlen(ft_getenv(mshell, temp)) + 1);
	}
}
//ft_strlen(result) + ft_strlen(envtmp) + 1

void	process_token(t_minishell *mshell, char *temp, char *result, int i[3])
{
	ft_strlcpy(temp, "", 1024);
	i[2] = -1;
	if (mshell->token[i[0]][i[1]] == '\'' && !mshell->quote)
	{
		while (mshell->token[i[0]][++i[1]] && mshell->token[i[0]][i[1]] != '\'')
			temp[++i[2]] = mshell->token[i[0]][i[1]];
		temp[++i[2]] = '\0';
		ft_strlcat(result, temp, (ft_strlen(result) + ft_strlen(temp) + 1));
	}
	else if (mshell->token[i[0]][i[1]] == '$' \
		&& (ft_isalnum(mshell->token[i[0]][i[1] + 1]) \
		|| mshell->token[i[0]][i[1] + 1] == '?' || \
		mshell->token[i[0]][i[1] + 1] == '_'))
		handle_expand(mshell, temp, result, i);
	else
		handle_others(mshell, temp, result, i);
}
//i[2] will be the last character before quote

void	check_dollarsign(t_minishell *mshell)
{
	char	result[1024];
	char	temp[1024];
	int		i[3];

	i[0] = -1;
	while (mshell->token[++i[0]])
	{
		i[1] = -1;
		ft_strlcpy(result, "", 1024);
		mshell->quote = 0;
		while (mshell->token[i[0]][++i[1]])
			process_token(mshell, temp, result, i);
		free(mshell->token[i[0]]);
		mshell->token[i[0]] = ft_strdup(result);
	}
}
