/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:32:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 01:25:46 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	init_minishell(t_minishell *minish, char **envp)
{
	minish->stdin_copy = dup(STDIN_FILENO);
	minish->stdout_copy = dup(STDOUT_FILENO);
	minish->last_exit = 0;
	minish->cwd = getcwd(NULL, 1024);
	minish->my_envp = NULL;
	minish->attr = malloc(sizeof(struct termios) * 2);
	minish->evars = set_env(envp);
	minish->cmds = NULL;
	tcgetattr(STDIN_FILENO, &minish->attr->default_attr);
	rebuild_envp(minish);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minish;

	(void)argv;
	if (argc != 1)
		return (0);
	init_minishell(&minish, envp);
	tcgetattr(STDOUT_FILENO, &minish.attr->modified_attr);
	minish.attr->modified_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &minish.attr->modified_attr);
	return (0);
}
