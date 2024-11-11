/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa <yyean-wa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:11:23 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/08/02 22:48:49 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t	a;
	long	nb;
	char	*str;

	nb = n;
	a = (n <= 0);
	while (n != 0 && ++a > 0)
		n = n / 10;
	str = malloc(sizeof(char) * (a + 1));
	if (str == NULL)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[a--] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[a--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*s = ft_itoa(42);
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		printf("%c", s[a]);
		a++;
	}
	printf("\n");
	return(0);
}
*/
