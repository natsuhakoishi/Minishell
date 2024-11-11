/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:16:06 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:14:48 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int a)
{
	if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'))
		return (1);
	else if (a >= '0' && a <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
    printf("%d\n", ft_isalnum('+'));
    return (0);
}
*/
