/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:06:20 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/24 15:22:35 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quit_3(int sigquit)
{
	(void)sigquit;
	printf("Quit: 3\n");
}

void	quit_subshell(int sigint)
{
	(void)sigint;
	printf("\n");
}

void	ft_sigint(int sigint)
{
	(void)sigint;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 1)
	{
		signal(SIGINT, quit_subshell);
		signal(SIGQUIT, quit_3);
	}
}
