/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:56:27 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/11/24 16:41:49 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

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
void	exit_free(t_minishell *mshell, t_list **lst);
void	ft_free(t_minishell *mshell, t_list **lst);
void	ft_free2(t_list *current);

//signal
void	ft_signal(int flag);
void	ft_sigint(int sigint);
void	quit_subshell(int sigint);
void	quit_3(int sigquit);

#endif
