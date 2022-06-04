/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/04 18:59:56 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ch_equality(char *str, t_env *tmp2, t_env *lst)
{
	if (strcmp(str, lst->name) == 0)
	{
		tmp2 = lst;
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
		free(tmp2);
	}
}

void	ft_unset(t_env *lst, t_cmd *cmd_lst)
{
	int i;
	t_env *tmp;
	t_env *tmp2;

	i = 0;
	tmp = lst;
	tmp2 = NULL;
	while (cmd_lst->argument[i])
	{
		while (lst->next != tmp)
		{
			ch_equality(cmd_lst->argument[i], tmp2, lst);
			lst = lst->next;
		}
		ch_equality(cmd_lst->argument[i], tmp2, lst);
		lst = tmp;
		i++;
	}
}
