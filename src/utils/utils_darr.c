/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_darr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:53:29 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 01:25:32 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_darr(char ***array)
{
	int	a;

	a = 0;
	if (*array == NULL)
		return ;
	while ((*array)[a] != NULL)
	{
		free((*array)[a]);
		a++;
	}
	free(*array);
	(*array) = NULL;
}
