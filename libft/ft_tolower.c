/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:29:11 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:40:45 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int a)
{
	if (a >= 'A' && a <= 'Z')
		a += 32;
	return (a);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_tolower('A'));
	return (0);
}
*/
