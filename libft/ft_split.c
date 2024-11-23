/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:27:04 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 22:02:35 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(const char *str, char c)
{
	size_t	a;
	size_t	count;

	a = 0;
	if (str[a] == '\0')
		return (0);
	count = 0;
	while (str[a] != '\0')
	{
		while (str[a] == c)
			a++;
		if (str[a] != '\0')
			count++;
		while (str[a] != c && str[a] != '\0')
			a++;
	}
	return (count);
}

static char	**ft_res(const char *s, char **list, size_t len, char c)
{
	int	a;

	a = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			list[a++] = ft_substr(s, 0, len);
			s += len;
		}
	}
	list[a] = NULL;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	list = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!list)
		return (0);
	ft_res(s, list, len, c);
	return (list);
}
/*
#include <stdio.h>

int main(void)
{
	char	str[] = "This is a sample string to split";
	char	d = ' ';
	char	**result = ft_split(str, d);
	int		i;

	i = 0;
	if (result)
	{
		while (result[i] != NULL)
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	else
	{
		printf("Split failed. Memory allocation error.\n");
	}
	return (0);
}
*/
