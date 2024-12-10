/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:37:55 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/10 15:17:47 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ensure all tokens carried smth;
//break away empty token & connect back
void	check_empty(t_minishell *mshell)
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

int	check_quote2(t_minishell *mshell, int qflag)
{
	if (qflag != 0)
	{
		printf("Error: Quotes.\n");
		mshell->exit_status = 130;
		return (1);
	}
	return (0);
}

int	check_quote(t_minishell *mshell)
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
		if (check_quote2(mshell, qflag) == 1)
			return (1);
	}
	return (0);
}
//qflag; true when first quote detected(open quote),
//		 false when second quote detected(close quote)