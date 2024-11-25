/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:37:55 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/25 18:54:51 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_emptystr(t_minishell *mshell)
{
	int	a;

	a = -1;
	while (mshell->token[++a])
	{
		if (!ft_strncmp(mshell->token[a], "", ft_strlen(mshell->token[a])))
		{
			free(mshell->token[a]);
			while (mshell->token[a])
			{
				mshell->token[a] = mshell->token[a + 1];
				a++;
			}
			a = -1;
		}
	}
}

int	check_quotes2(t_minishell *mshell, int qflag)
{
	if (qflag != 0)
	{
		printf("Error: Quotes.\n");
		mshell->exit_status = 130;
		return (1);
	}
	return (0);
}
//close quote 0, open quote 1 - qflag
//QUESTION: check for case like this ? ex. "hello, no closing quote for this

int	check_quotes(t_minishell *mshell)
{
	int	a;
	int	b;
	int	qflag;

	a = -1;
	qflag = 0;
	while (mshell->token[++a])
	{
		b = -1;
		while (mshell->token[a][++b])
		{
			if (mshell->token[a][b] == '\'' || mshell->token[a][b] == '\"')
			{
				if (qflag == 0)
					qflag = mshell->token[a][b];
				else if (qflag == mshell->token[a][b])
					qflag = 0;
			}
		}
		if (check_quotes2(mshell, qflag) == 1)
			return (1);
		return (0);
	}
}
