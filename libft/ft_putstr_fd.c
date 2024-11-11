/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:46:14 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 19:26:50 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	a;

	if (!s)
		return ;
	a = 0;
	if (s[a] == '\0')
		return ;
	while (s[a] != '\0')
	{
		ft_putchar_fd(s[a], fd);
		a++;
	}
}
/*
int	main(void)
{
	ft_putstr_fd("Maimai DX Buddies", 1);
	return (0);
}
*/
