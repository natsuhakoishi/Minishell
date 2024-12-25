/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:06:20 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/26 00:53:17 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quit_3(int sigquit)
{
	(void)sigquit;
	printf("Quit (core dumped)\n");
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

void	hd_action(int sigint)
{
	(void)sigint;
	unlink(".tmp");
	exit(42);
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
	else if (flag == 2)
	{
		signal(SIGINT, hd_action);
		signal(SIGQUIT, SIG_IGN);
	}
}
