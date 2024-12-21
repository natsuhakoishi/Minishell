/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:56:27 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/21 12:36:18 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "../libft/libft.h"

# define BUFFER 10000

typedef struct s_minishell
{
	char			**token;
	char			**envp;
	char			cwd[1024];
	int				in_backup;
	int				out_backup;
	int				in_fd;
	int				out_fd;
	int				exit_status;
	int				quote;
	struct termios	modified_attr;
	struct termios	default_attr;
}	t_minishell;

//utils
char	*ft_getenv(t_minishell *mshell, char *evar);
int		check_built_in(t_list *lst);
void	envp_sorting(char **envp, int size);
void	err_msg(t_minishell *mshell, int exit_status, char *msg, char *arg);
void	lexem_update(t_list *lst, int i);
void	print_node(t_list *lst);

//exit & free memory related

void	free_exit(t_minishell *mshell, t_list **lst, int freed);
void	ft_free(t_minishell *mshell, t_list **lst, int freed);
// void	free_node(t_list *current);
void	free_dptr(char **ptr);

//signal

void	ft_signal(int flag);
void	ft_sigint(int sigint);
void	quit_subshell(int sigint);
void	quit_3(int sigquit);

//lexer

char	**lexer(char *input, const char *op);
int		lx_split(char **tokens, const char *input, const char *op);
void	lx_split2(char **tokens, const char *input, const char *op, int i[3]);

//parser

int		check_quote(t_minishell *mshell);
int		check_quote2(t_minishell *mshell, int qflag);
void	check_empty(t_minishell *mshell);

//variable expansion

void	check_dollarsign(t_minishell *mshell);
void	process_token(t_minishell *mshell, char *temp, char *result, int i[3]);
void	handle_expand(t_minishell *mshell, char *temp, char *result, int i[3]);
void	handle_others(t_minishell *mshell, char *temp, char *result, int i[3]);

//pre-execution & pipeline

int		redirection(t_minishell *mshell, t_list *lst);
void	here_doc(t_minishell *mshell, t_list *lst);
// void	input_setup(t_minishell *mshell, t_list *lst);
// void	output_setup(t_minishell *mshell, t_list *lst);

//execution

void	execution(t_minishell *mshell, t_list *lst);
void	built_in(t_minishell *mshell, t_list *lst);
// void	child_management(t_minishell *mshell, t_list *lst);
void	child_process(t_minishell *mshell, t_list *lst);

//execution - built-ins

void	builtin_exit(t_minishell *mshell, t_list *lst);
void	builtin_env(t_minishell *mshell, t_list *lst);
void	builtin_cd(t_minishell *mshell, t_list *lst);
void	builtin_echo(t_minishell *mshell, t_list *lst);
void	builtin_unset(t_minishell *mshell, t_list *lst);
void	builtin_export(t_minishell *mshell, t_list *lst);
void	executable(t_minishell *mshell, t_list *lst);

#endif
