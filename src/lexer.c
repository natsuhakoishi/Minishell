/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:46:54 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/28 04:53:22 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//split as token when certain conditions meet
void	lx_split2(char **tokens, const char *input, const char *op, int i[3])
{
	if ((input[i[0]] == ' ' || i[0] == (int)ft_strlen(input) \
			|| (input[i[0]] && ft_strchr(op, input[i[0]]))) && i[2] >= 0)
	{
		if ((i[0] - i[2]) != 0)
			tokens[++i[1]] = ft_substr(input, i[2], i[0] - i[2]);
		if (input[i[0]] && ft_strchr(op, input[i[0]]))
		{
			i[2] = i[0];
			if ((input[i[0]] == '>' && input[i[0] + 1] == '>') \
				|| (input[i[0]] == '<' && input[i[0] + 1] == '<'))
			{
				tokens[++i[1]] = ft_substr(input, i[2], 2);
				i[0]++;
			}
			else
				tokens[++i[1]] = ft_substr(input, i[2], 1);
		}
		i[2] = -1;
	}
}
//1th if-statement:
//2th if-statement: check for operator

//split input into multiple tokens, and return the total number of tokens
//will ignore content in quote & double quote, as subject asked
int	lx_split(char **tokens, const char *input, const char *op)
{
	int	i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (++i[0] <= (int)ft_strlen(input))
	{
		if (input[i[0]] != ' ' && i[2] < 0)
			i[2] = i[0];
		if (input[i[0]] == '\"')
			while (input[++i[0]] && input[i[0]] != '\"')
				;
		else if (input[i[0]] == '\'')
			while (input[++i[0]] && input[i[0]] != '\'')
				;
		lx_split2(tokens, input, op, i);
	}
	tokens[++i[1]] = NULL;
	return (i[1]);
}
//i[0] stored index
//i[1] stored current position of token @ start position of current token
//i[2] is pos word start as word count

void	lexer_copy(char **ntokens, char **tokens, int len)
{
	int	a;

	a = -1;
	while (++a <= len)
		ntokens[a] = tokens[a];
	free(tokens);
}

//return tokens with optimal memory
char	**lexer(char *input, const char *op)
{
	int		len;
	char	**tokens;
	char	**ntokens;

	if (input == NULL || !ft_strncmp(input, "", ft_strlen(input)))
		return (NULL);
	tokens = malloc(sizeof(char *) * BUFFER + 1);
	if (!tokens)
		return (NULL);
	len = lx_split(tokens, input, op);
	if (len == 0)
	{
		free(tokens);
		return (NULL);
	}
	ntokens = malloc(sizeof(char *) * (len + 1));
	if (!ntokens)
	{
		free(tokens);
		return (NULL);
	}
	lexer_copy(ntokens, tokens, len);
	return (ntokens);
}
