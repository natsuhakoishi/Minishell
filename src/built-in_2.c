/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgoh <zgoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 03:58:30 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/11 03:57:19 by zgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle 'unset'
//>no args
//ex. lexem[1] will be the key only
void	builtin_unset(t_minishell *mshell, t_list *lst)
{
	char	*key;
	int		i;

	i = -1;
	if (lst->lexem[1])
	{
		lst->lexem[1] = remove_quote(lst->lexem[1]);
		while (mshell->envp[++i])
		{
			if (ft_strpos(mshell->envp[i], "="))
				key = ft_substr(mshell->envp[i], 0, ft_strpos(mshell->envp[i], "="));
			else
				key = ft_substr(mshell->envp[i], 0, ft_strlen(mshell->envp[i]));
			if (!ft_strncmp(lst->lexem[1], mshell->envp[i], ft_strlen(temp)))
			{
				free(mshell->envp[i]);
				mshell->envp[i] = mshell->envp[i + 1];
			}
		}
		// mshell->envp[i] = NULL;
	}
	mshell->exit_status = 0;
}
//fix partial same can remove the env (correction: should 100)
//fix current only accept one args; forget liao should be more

//update list of envp
//>either added a new envp / replace old envp with new value
void	update_mshell_envp(t_minishell *mshell, char *new, int sign)
{
	int	i;

	i = 0;
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
//*not given args
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
}

//handle 'export'
//>no args / multiple args; follow identifier naming rule
void	builtin_export(t_minishell *mshell, t_list *lst)
{
	int		i;
	char	*word;

	i = 0;
	if (lst->lexem[1] == NULL)
		print_mshell_envp(mshell);
	else
	{
		while (lst->lexem[++i])
		{
			if (!ft_isalpha(lst->lexem[i][0]) && lst->lexem[i][0] != '_')
			{
				printf("Minishell: export: %s not a valid identifier\n", \
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
