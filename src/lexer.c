/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:46:54 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/24 16:35:19 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lx_split2(char **tokens, const char *input, const char *op, int i[3])
{
	if ((input[i[0]] == ' ' || i[0] == ft_strlen(input)
		|| (input[i[0]] && ft_strchr(op, input[i[0]])))
		&& i[2] >= 0)
	{
		if ((i[0] - i[2]) != 0)
			tokens[++i[1]] = ft_substr(input, i[2], i[0] - i[2]);
		if (input[i[0]] && ft_strchr(op, input[i[0]]))
		{
			i[2] = i[0];
			if ((input[i[0]] == '>' && input[i[0] + 1] == '>')
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

int	lx_split(char **tokens, const char *input, const char *op)
{
	int	i[3];

	i[0] = -1;//index
	i[1] = -1;//cur pos of token
	i[2] = -1;//pos word start as word count
	while (++i[0] <= ft_strlen(input))
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

char	**lexer(char *input, const char *op)
{
	int		len;
	int		a;
	char	**tokens;

	a = -1;
	if (!input)
		return (NULL);
	tokens = malloc(sizeof(char *) * BUFFER);
	len = lx_split(tokens, input, op);
	while (tokens[++a])
		free(tokens[a]);
	free(tokens);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	lx_split(tokens, input, op);
	return (tokens);
}
