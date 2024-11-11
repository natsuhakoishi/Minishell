/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:03:28 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/12 01:22:13 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef ECHOCTL
#define ECHOCTL 0001000
#endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <termios.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_signal
{
	struct termios	default_attr;
	struct termios	modified_attr;
}	t_signal;

typedef struct s_env
{
	char	*str;
	int		printed;
}	t_env;

typedef struct s_cmd
{
	char	**cmd;
}	t_cmd;

typedef struct s_lst
{
	int				fd_in;
	int				fd_out;

	t_env			env;
	t_cmd			cmd;

	struct s_lst	*next;
}	t_lst;

typedef struct s_minishell
{
	int			stdin_copy;
	int			stdout_copy;
	int			last_exit;

	char		*line;
	char		*cwd;
	char		**token;
	char		**my_envp;

	t_signal	*attr;
	t_lst		*evars;
	t_lst		*cmds;
}	t_minishell;

void	rebuild_envp(t_minishell *minish);
t_lst	*set_env(char **envp);

void	free_darr(char ***array);

t_lst	*init_list(char *new);

void	ft_lstadd_back(t_lst **lst, t_lst *new);
int		ft_lstsize(t_lst *lst);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);

#endif
