/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:44:23 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/25 02:11:03 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpos(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (*needle == '\0' || needle == NULL)
		return (0);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
