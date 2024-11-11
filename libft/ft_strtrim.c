/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:06:02 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:40:08 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_flag(char c, char const *set)
{
	size_t	a;

	a = 0;
	while (set[a] != '\0')
	{
		if (set[a] == c)
			return (1);
		a++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	size_t	init;
	size_t	last;
	char	*result;

	a = 0;
	init = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[init] && ft_flag((s1[init]), set))
		init++;
	last = ft_strlen(s1);
	while (last > init && ft_flag(s1[last - 1], set))
		last--;
	result = malloc(sizeof(char) * (last - init + 1));
	if (result == NULL)
		return (NULL);
	while (init < last)
		result[a++] = s1[init++];
	result[a] = '\0';
	return (result);
}
/*
#include <stdio.h>

int main()
{
	const char *input = "....xxhello...x..x";
	const char *set = ".x";

	char *trimmed = ft_strtrim(input, set);

	if (trimmed)
	{
		printf("Original String: %s\n", input);
		printf("Trimmed String: %s\n", trimmed);
		free(trimmed);
    }
	else
	{
		printf("Memory allocation error or invalid input.\n");
	}
	return (0);
}
*/
