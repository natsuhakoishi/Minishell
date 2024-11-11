/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa <yyean-wa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:12:12 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/10/16 10:05:31 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long	a;
	long	sign;
	long	result;

	a = 0;
	sign = 1;
	result = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32)
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			sign *= -1;
		a++;
	}
	while (ft_isdigit(str[a]))
	{
		result *= 10;
		result += (str[a++] - '0');
	}
	return (sign * result);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char *str = "-89172shu";
	int	res;

	res = ft_atoi(str);
	printf("%d\n", res);
	printf("%d\n", atoi(str));
	return (0);
}
*/
