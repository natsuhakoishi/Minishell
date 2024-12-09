/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 03:58:30 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/09 19:30:50 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ex. './' and '/'
//absolute path of a command;l ex. /usr/bin/ls
//executeable file; ex. ./minishell ./pipex
void	executable(t_minishell *mshell, t_list *lst)
{
	int	pid;

	if (access(lst->lexem[0], F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(lst->lexem[0], lst->lexem, mshell->envp);
		else if (pid > 0)
		{
			waitpid(pid, &mshell->exit_status, 0);
			mshell->exit_status = mshell->exit_status % 255;
		}
	}
	else
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(lst->lexem[0]);
		mshell->exit_status = 127;
		return ;
	}
	mshell->exit_status = 0;
}
//todo have a idea to put path resolution in here too
//		ex. pass in ../ only, or / or ./ or subdirectory

void	builtin_unset(t_minishell *mshell, t_list *lst)
{
	char	*temp;
	int		i;

	i = -1;
	if (!lst->lexem[1])
		return ;
	// ft_strlcpy(temp, lst->lexem[1], ft_strlen(lst->lexem[1]));
	temp = remove_quote(lst->lexem[1]);
	while (mshell->envp[++i])
	{
		if (!ft_strncmp(temp, mshell->envp[i], ft_strlen(temp)))
			mshell->envp[i] = mshell->envp[i + 1];
	}
	mshell->exit_status = 0;
}

void	builtin_export(t_minishell *mshell, t_list *lst)
{
	int		i;
	char	*word;

	i = -1;
	if (lst->lexem[1] == NULL)
		print_mshell_envp(mshell);
	else
	{
		while (lst->lexem[++i])
		{
			if (!ft_isalpha(lst->lexem[i][0]) && lst->lexem[i][0] != '_')
			{
				printf("Minishell: export: %s not a valid identifier", \
						lst->lexem[i]);
				mshell->exit_status = 1;
				return ;
			}
			else
			{
				word = remove_quote(lst->lexem[i]);
				update_mshell_envp(mshell, word, ft_strpos(word, "="));
			}
		}
	}
	mshell->exit_status = 0;
}

//update list of envp; either added a new envp / replace old envp with new value
void	update_mshell_envp(t_minishell *mshell, char *new, int sign)
{
	int	i;

	i = -1;
	if (new[ft_strpos(new, "=") + 1] == '\0')//NULL value
		ft_strlcat(new, "\"\"", (ft_strlen(new) + 2));
	while (mshell->envp[++i])
	{
		if (!ft_strncmp(mshell->envp[i], new, sign - 1)) //existed envp; replace old_value with new_value
		{
			free(mshell->envp[i + 1]);
			mshell->envp[i + 1] = ft_strdup(new);
			break ;
		}
		else if (mshell->envp[i + 1] == NULL) //surely is new envp then
		{
			free(mshell->envp[i + 1]);
			mshell->envp[i + 1] = ft_strdup(new);
			mshell->envp[i + 2] = NULL;
			break ;
		}
	}
}

//list out all envp
void	print_mshell_envp(t_minishell *mshell)
{
	int		i;
	char	*temp;
	int		sign;
	int		size;

	i = -1;
	while (mshell->envp[++i])
		;
	size = i;
	i = -1;
	envp_sorting(mshell->envp, size);
	while (mshell->envp[++i])
	{
		if (ft_strchr(mshell->envp[i], '='))
		{
			sign = ft_strpos(mshell->envp[i], "=");
			temp = ft_substr(mshell->envp[i], 0, sign - 1);
			printf("declare -x %s\"%s\"\n", temp, \
					ft_strchr(mshell->envp[i], '=') + 1);
		}
		else
			printf("declare -x %s\n", mshell->envp[i]);
	}
}
