/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:54:49 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/23 15:56:45 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_command(t_list **lst, t_minishell *mshell)
{
	printf("done split\n");
}

// //split based on pipe operator & duplicate value to linked list
// void	split_command(t_list **lst, t_minishell *mshell)
// {
// 	char	**temp;
// 	int		a;
// 	int		b;

// 	a = -1;
// 	b = -1;
// 	temp = malloc(sizeof(char *) * (BUFFER + 1));
// 	for (int i = 0; mshell->token && mshell->token[i]; ++i)
// 		printf("token[%d]: %s\n", i, mshell->token[i]); //Debug
// 	while (mshell->token[++a])
// 	{
// 		if (!ft_strncmp(mshell->token[a], "|", 1))
// 		{
// 			temp[++b] = NULL;
// 			ft_lstadd_back(lst, ft_lstnew(temp));
// 			free(temp);
// 			b = -1;
// 			temp = malloc(sizeof(char *) * (BUFFER + 1));
// 			if (!temp)
// 				exit(1);
// 		}
// 		else{ printf("lexem %s\n", mshell->token[a]);
// 			temp[++b] = ft_strdup(mshell->token[a]);}
// 	}
// 	temp[++b] = NULL;
// 	ft_lstadd_back(lst, ft_lstnew(temp));
// 	// free(temp);
// }
// printf("token[%d]: %s\n", a, mshell->token[a]); //Debug
//TODO actually will have memory unreachable issue

//Minishell's prompt & "scanf()"
void	ft_input(t_minishell *mshell)
{
	char	*input;
	char	prompt[100];

	getcwd(mshell->cwd, sizeof(mshell->cwd));
	ft_strlcpy(prompt, "\033[33mMinishell | \033[4;34m", 30);
	ft_strlcat(prompt, mshell->cwd, 100);
	ft_strlcat(prompt, " \033[0m> \033[0m", 100);
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
//memo what if input line itselt have ady 100?

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
		free_exit(mshell, &lst, 0);
	while (1)
	{
		ft_signal(0);
		ft_input(mshell);
		if (!check_quote(mshell))
		{
			check_dollarsign(mshell);
			check_empty(mshell);
			printf("--before split command\n");
			printf("token:\n");
			for(int i = 0; mshell->token[i]; ++i)
				printf("\t %s", mshell->token[i]);
			split_command(&lst, mshell);
			printf("--after split command\n");
			print_node(lst);
			tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
			if (redirection(mshell, lst))
				execution(mshell, lst);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &mshell->modified_attr);
		ft_free(mshell, &lst, 1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &mshell->default_attr);
}
