/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 16:14:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ch_equality(char *str, t_env *lst)
{
	t_env *tmp2;

	if (ft_strcmp(str, lst->name) == 0)
	{
		tmp2 = lst;
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
		free(tmp2->name);
		free(tmp2);
		return (1);
	}
	return (0);
}

void	ft_unset(t_env *lst, t_cmd *cmd_lst)
{
	int i;
	t_env *tmp;

	i = 1;
	tmp = lst;
	while (cmd_lst->argument[i])
	{
		while (lst->next != tmp)
		{
			if (ch_equality(cmd_lst->argument[i], lst) == 1)
				lst = tmp;
			lst = lst->next;
		}
		if (ch_equality(cmd_lst->argument[i], lst) == 1)
			lst = tmp;
		lst = tmp;
		i++;
	}
}
