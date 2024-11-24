/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:54:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/25 02:11:56 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_input(t_minishell *mshell)
{
	char	*input;
	char	prompt[100];

	getcwd(mshell->cwd, sizeof(mshell->cwd));
	ft_strlcpy(prompt, "Minishell | ", 13);
	ft_strlcat(prompt, mshell->cwd, 100);
	ft_strlcat(prompt, " > ", 100);
	input = readline(prompt);
	if (!input)
		exit(0);
	if (ft_strncmp(input, "", 1))
		add_history(input);
	mshell->token = lexer(input, "<>|");
	if (!mshell->exit_status)
		mshell->exit_status = 0;
	free(input);
}

void	init_minishell(t_minishell *mshell, char **envp)
{
	mshell->envp = envp;
	mshell->quote = 0;
	tcgetattr(STDIN_FILENO, &mshell->default_attr);
	mshell->modified_attr = mshell->default_attr;
	mshell->modified_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &mshell->modified_attr);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mshell;
	t_list		**lst;

	mshell = malloc(sizeof(t_minishell));
	lst = malloc(sizeof(t_list));
	init_minishell(mshell, envp);
	if (argc > 1)
		exit_free(mshell, lst);
	while (1)
	{
		ft_signal(0);
		ft_input(mshell);
		if (!check_quotes(mshell))
		{
			check_dollar(mshell);
			check_emptystr(mshell);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &mshell->modified_attr);
		ft_free(mshell, lst);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
}
