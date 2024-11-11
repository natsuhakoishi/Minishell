/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:33:38 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 18:36:38 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if ((unsigned char)c == 0)
		return ((char *)(str + ft_strlen(str)));
	while (*str)
	{
		if (*str == (unsigned char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "Maimai DX Festival";
	char	c = 'a';

	if (ft_strchr(str, c) != NULL)
	{
		printf("%s\n", ft_strchr(str, c));
		printf("%s\n", strchr(str, c));
	}
	else
		printf("Not found.\n");
	return (0);
}
*/
