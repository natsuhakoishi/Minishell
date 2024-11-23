/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:57:44 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 22:18:57 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	a;
	size_t	b;

	if (!str && !len)
		return (0);
	a = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[a] && a < len)
	{
		b = 0;
		while ((str[a + b] && to_find[b] == str[a + b]) && (a + b < len))
		{
			if (to_find[b + 1] == 0)
				return ((char *)(&str[a]));
			b++;
		}
		a++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	str[] = "Maimai DX Festival Plus";
	const char	tf[] = "Festival";
	size_t	len = 15;

	if (ft_strnstr(str, tf, len) != NULL)
	{
		printf("%s\n", tf);
	}
	else
	{
		printf("Not found.\n");
	}
	return (0);
}
*/
