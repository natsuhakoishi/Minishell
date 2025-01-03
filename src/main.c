/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:54:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/31 13:08:16 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

void	split_command(t_list **lst, t_minishell *mshell)
{
	char	**temp;
	int		a;
	int		b;

	a = -1;
	b = -1;
	if (!mshell->token[0])
		return ;
	temp = malloc(sizeof(char *) * (BUFFER + 1));
	while (mshell->token[++a])
	{
		if (!ft_strncmp(mshell->token[a], "|\0", 2))
		{
			temp[++b] = NULL;
			ft_lstadd_back(lst, ft_lstnew(temp));
			temp = malloc(sizeof(char *) * (BUFFER + 1));
			b = -1;
		}
		else
			temp[++b] = ft_strdup(mshell->token[a]);
	}
	temp[++b] = NULL;
	ft_lstadd_back(lst, ft_lstnew(temp));
	free_dptr(mshell->token);
}

//Minishell's prompt & "scanf()"
void	ft_input(t_minishell *mshell)
{
	char	*input;
	char	prompt[100];

	mshell->here_doc = 0;
	mshell->flag = 1;
	getcwd(mshell->cwd, sizeof(mshell->cwd));
	ft_strlcpy(prompt, "\033[33mMinishell | \033[4;34m", 30);
	ft_strlcat(prompt, mshell->cwd, 100);
	ft_strlcat(prompt, " \033[0m> \033[0m", 100);
	input = readline(prompt);
	if (!input)
	{
		g_exit_code = 0;
		exit(g_exit_code);
	}
	if (ft_strncmp(input, "", 1))
		add_history(input);
	mshell->token = lexer(input, "<>|");
	if (g_exit_code == 130 || g_exit_code == 131)
		mshell->exit_status = g_exit_code;
	g_exit_code = 0;
	free(input);
}

void	init_minishell(t_minishell *mshell, char **envp)
{
	mshell->envp = envp;
	mshell->quote = 0;
	mshell->exit_status = 0;
	mshell->token = NULL;
	tcgetattr(STDIN_FILENO, &mshell->default_attr);
	mshell->modified_attr = mshell->default_attr;
	mshell->modified_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &mshell->modified_attr);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mshell;
	t_list		*lst;

	mshell = malloc(sizeof(t_minishell));
	lst = NULL;
	init_minishell(mshell, envp);
	if (argc > 1 || argv[1])
		exit(1);
	while (1)
	{
		ft_signal(0);
		ft_input(mshell);
		if (mshell->token != NULL && !check_quote(mshell) && check_pipe(mshell))
		{
			check_dollarsign(mshell);
			check_empty(mshell);
			split_command(&lst, mshell);
			tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
			if (redirection(mshell, lst))
				execution(mshell, lst);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &mshell->modified_attr);
		free_lst(mshell, &lst);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
}
