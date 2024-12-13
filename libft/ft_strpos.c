/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:44:23 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/11 17:42:04 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//return value: index of needle in haystack (first character)
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
		while (needle[j] == haystack[i + j])//found character matched betw. needle & haystack
		{
			if (needle[j + 1] == '\0')//return the index of character fonud in haystack; if finish compared needle
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
