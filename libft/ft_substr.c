/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:13:31 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:40:28 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;
	size_t	a;

	if (!s)
		return (0);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	size = len;
	sub = malloc(sizeof(char) * (size + 1));
	if (sub == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		*sub = '\0';
		return (sub);
	}
	a = 0;
	while (a < len)
	{
		sub[a] = s[start + a];
		a++;
	}
	sub[a] = '\0';
	return (sub);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*str = "Good bye, Merry-Go-Round";
	unsigned int start;
	size_t	len;
	char	*res;

	start = 2;
	len = 5;
	res = ft_substr(str, start, len);
	if (res != NULL)
	{
		printf("%s\n", res);
		free(res);
	}
	else
	{
		printf("Error\n");
	}
	return (0);
}
*/
