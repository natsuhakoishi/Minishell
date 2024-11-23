/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:31:15 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:34:44 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	a;
	char	*str;
	char	*cpy;

	str = (char *)malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	cpy = str;
	a = 0;
	while (s[a] != '\0')
	{
		str[a] = s[a];
		a++;
	}
	str[a] = '\0';
	return (cpy);
}
/*
#include <stdio.h>

int	main(void)
{
	char	a[] = "dwhdvyuqwgdyugweygd";
	char	*b = ft_strdup(a);

	printf("%s\n", b);
	free(b);
	return (0);
}
*/
