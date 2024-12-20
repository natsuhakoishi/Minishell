/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 03:58:30 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/21 03:04:17 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset_2(t_minishell *mshell, int j)
{
	while (mshell->envp[j])
	{
		mshell->envp[j] = mshell->envp[j + 1];
		++j;
	}
	mshell->envp[j] = NULL;
}

//handle 'unset'
//>no args / multiple valid args
//ex. lexem[1] will be the key only & not include value
void	builtin_unset(t_minishell *mshell, t_list *lst)
{
	int		i;
	int		j;
	char	*arg;
	char	*key;

	i = 0;
	while (lst->lexem[++i])
	{
		arg = ft_strtrim(lst->lexem[i], "\'\"");
		j = -1;
		while (mshell->envp[++j])
		{
			if (ft_strchr(mshell->envp[j], '='))
				key = ft_substr(mshell->envp[j], 0, \
						ft_strpos(mshell->envp[j], "="));
			else
				key = ft_strdup(mshell->envp[j]);
			if (!ft_strncmp(arg, key, ft_strlen(arg) + 1))
				builtin_unset_2(mshell, j);
			free (key);
		}
		free (arg);
	}
	mshell->exit_status = 0;
}
//todosupposed break; after unset_2 been called, but no more line

//update list of envp
//>3 situation; existed envp w/ value, existed envp w/o value, or new envp
//>arg: argument without quote
//>sign: index of '='
void	update_mshell_envp(t_minishell *mshell, char *arg, int sign)
{
	int	i;

	i = -1;
	while (mshell->envp[++i])
	{
		if (!ft_strncmp(mshell->envp[i], arg, sign) && sign)
		{
			mshell->envp[i] = ft_strdup(arg);
			break ;
		}
		else if (!ft_strncmp(mshell->envp[i], arg, ft_strlen(arg)))
		{
			mshell->envp[i] = ft_strdup(arg);
			break ;
		}
		else if (mshell->envp[i + 1] == NULL)
		{
			free(mshell->envp[i + 1]);
			mshell->envp[i + 1] = ft_strdup(arg);
			mshell->envp[i + 2] = NULL;
			break ;
		}
	}
	if (mshell->exit_status != 1)
		mshell->exit_status = 0;
}

//behaviour when no args passed in
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
			temp = ft_substr(mshell->envp[i], 0, sign);
			printf("declare -x %s=\"%s\"\n", temp, \
					ft_strchr(mshell->envp[i], '=') + 1);
		}
		else
			printf("declare -x %s\n", mshell->envp[i]);
	}
	free(temp);
	mshell->exit_status = 0;
}

//handle 'export'
//>no args / multiple args; (follow identifier naming rule)
void	builtin_export(t_minishell *mshell, t_list *lst)
{
	int		i;
	char	*arg;

	i = 0;
	if (lst->lexem[1] == NULL)
		print_mshell_envp(mshell);
	else
	{
		while (lst->lexem[++i])
		{
			if (!ft_isalpha(lst->lexem[i][0]) && lst->lexem[i][0] != '_')
			{
				err_msg(mshell, 1, \
						"Minishell: export: \'%s\': not a valid identifier\n", \
						lst->lexem[i]);
				continue ;
			}
			else
			{
				arg = ft_strtrim(lst->lexem[i], "\'\"");
				update_mshell_envp(mshell, arg, ft_strpos(arg, "="));
				free(arg);
			}
		}
	}
}
