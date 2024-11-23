/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:44:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 19:07:43 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	len;

	if (size > 0 && n > UINT_MAX / size)
		return (0);
	len = n * size;
	ptr = malloc(len);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, len);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	size_t	num;
	size_t	size;
	int		*str;
	size_t	a;

	a = 0;
	num = 5;
	size = sizeof(int);
	str = ft_calloc(num, size);
	if (str)
	{
		while (a < num)
		{
			printf("%d ", str[a]);
			a++;
		}
		printf("\n");
		free (str);
	}
	else
	{
		printf("Failed.");
	}
	return (0);
}
*/
