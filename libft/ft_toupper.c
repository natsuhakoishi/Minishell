/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:25:18 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:41:01 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int a)
{
	if (a >= 'a' && a <= 'z')
		a -= 32;
	return (a);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_toupper('a'));
	return (0);
}
*/
