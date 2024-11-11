/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:13:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 18:37:39 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*a;

	a = 0;
	while (*str)
	{
		if (*str == (unsigned char)c)
			a = (char *)str;
		str++;
	}
	if (c == 0)
		return ((char *)str);
	return ((char *)a);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "Maimai DX Festival";
	char	c = 'a';

	if (ft_strrchr(str, c) != NULL)
	{
		printf("%s\n", ft_strrchr(str, c));
		printf("%s\n", strrchr(str, c));
	}
	else
		printf("Not found.\n");
	return (0);
}
*/
