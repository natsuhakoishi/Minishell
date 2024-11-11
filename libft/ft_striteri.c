/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:25:22 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:35:10 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	a;

	if (!s || !f)
		return ;
	a = 0;
	while (s[a] != '\0')
	{
		(*f)(a, &s[a]);
		a++;
	}
}
/*
#include <stdio.h>

void ft_print(unsigned int index, char *c)
{
	printf("%d: %c\n", index, *c);
}

int main(void)
{
	char *str = "Chia Slander";

	ft_striteri(str, ft_print);
	return (0);
}
*/
