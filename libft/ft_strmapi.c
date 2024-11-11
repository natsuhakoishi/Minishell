/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:50 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:37:40 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	a;
	char	*result;

	if (!s)
		return (NULL);
	a = 0;
	while (s[a] != '\0')
		a++;
	result = malloc(sizeof(char) * (a + 1));
	if (result == NULL)
		return (NULL);
	a = 0;
	while (s[a] != '\0')
	{
		result[a] = (*f)(a, s[a]);
		a++;
	}
	result[a] = '\0';
	return (result);
}
/*
#include <stdio.h>

char to_upper(unsigned int index, char c)
	{
		(void)index;
		if (c >= 'a' && c <= 'z')
			return (c - ('a' - 'A'));
		else
			return (c);
	}

int	main(void)
{
	char *str = "Coca Cola is diabetes speed run pack essentials.";
	char *result = ft_strmapi(str, to_upper);

	if (result != NULL)
	{
		printf("%s\n", result);
		free(result);
	}
	return (0);
}
*/
