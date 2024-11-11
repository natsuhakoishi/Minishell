/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 02:36:36 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:38:23 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 && *s2) && n > 0)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s1[] = "haha";
	char	s2[] = "ahah";

	printf("%d\n", ft_strncmp(s1, s2, 1));
	printf("%d\n", strncmp(s1, s2, 1));
	return (0);
}
*/
