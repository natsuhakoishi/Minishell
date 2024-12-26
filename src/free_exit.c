/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:30:05 by zgoh              #+#    #+#             */
/*   Updated: 2024/12/26 21:59:47 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char **str)
{
	int	i;

	if (!str || !(*str))
		return ;
	// printf("Start: double pointer(%p)\n", str); //Debug
	i = -1;
	while (str[++i])
	{
		// printf("Freeing string [%d]: %p\n", i, str[i]); //Debug
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	ft_free(t_minishell *mshell, t_list **lst, int freed)
{
	t_list	*next;
	t_list	*current;

	// printf("ft_free trigger\n"); //Debug
	if (freed)
	{
		(void)mshell;
		// if (mshell && mshell->token){
		// 	// printf("Freeing mshell->token: %p\n", mshell->token); //Debug
		// 	free_dptr(mshell->token);}
		if (lst && *lst)
		{
			current = *lst;
			while (current)
			{
				next = current->next;
				if (current->lexem && *current->lexem){
					// printf("Freeing lst->lexem: %p\n", current->lexem); // Debug
					free_dptr(current->lexem);}
				// printf("Freeing current node: %p\n", current); //Debug
				free(current);
				current = next;
			}
			*lst = NULL;
		}
	}
}

void	free_exit(t_minishell *mshell, t_list **lst, int freed)
{
	int	code;

	code = mshell->exit_status;
	// printf("Freeing resources in free_exit...\n"); //Debug
	ft_free(mshell, lst, freed);
	if (lst && freed)
	{
		// printf("Freeing lst: %p\n", lst); //Debug
		free(lst);
		lst = NULL;
	}
	if (mshell && freed)
	{
		// printf("Freeing mshell: %p\n", mshell); //Debug
		free(mshell);
		mshell = NULL;
	}
	// printf("Exiting with code: %d\n", code); //Debug
	exit(code);
}
