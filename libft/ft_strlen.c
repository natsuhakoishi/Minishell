/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:29:26 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:37:16 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*str++ != '\0')
		a++;
	return (a);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%ld\n", ft_strlen("haha"));
	return (0);
}
*/
