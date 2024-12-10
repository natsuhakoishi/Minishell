/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:54:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/10 15:16:10 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//split based on pipe operator
//result: each command seperate by pipe & stored in individual node
void	split_command(t_list **lst, t_minishell *mshell)
{
	char	**temp;
	int		a;
	int		b;

	a = -1;
	b = -1;
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
}
//repeated malloc() should actually cause memory leaks;
//	but before malloc again, we added temp to linked list,
//	then malloc give us new address
//https://chatgpt.com/share/6749ebc2-48e8-8000-842f-798fccf2a9c4
//https://chatgpt.com/share/6749f8b6-5d70-8000-9608-c2131dd03860

//Minishell's prompt & "scanf()"
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
	mshell->execve_status = 0;
	tcgetattr(STDIN_FILENO, &mshell->default_attr);
	mshell->modified_attr = mshell->default_attr;
	mshell->modified_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &mshell->modified_attr);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mshell;
	t_list		*lst;

	(void)argv;
	mshell = malloc(sizeof(t_minishell));
	lst = malloc(sizeof(t_list));
	init_minishell(mshell, envp);
	if (argc > 1)
		free_exit(mshell, &lst);
	while (1)
	{
		ft_signal(0);
		ft_input(mshell);
		if (!check_quote(mshell))
		{
			check_dollarsign(mshell);
			check_empty(mshell);
			split_command(&lst, mshell);
			tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
			if (redirection(mshell, lst))
				execution(mshell, lst);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &mshell->modified_attr);
		ft_free(mshell, &lst);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
}
//quote not closing, consider as error