/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 07:29:45 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/14 13:27:22 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_lst_len(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst->next != tmp)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}

int	get_args_len(t_cmd *cmd_lst)
{
	int		i;

	i = 0;
	while (cmd_lst->argument[i])
		i++;
	return (i);
}

int	iter_diff(t_env *lst, t_env *new_node)
{
	int	i;

	i = 0;
	while (lst->name[i] == new_node->name[i])
		i++;
	if (lst->name[i] < new_node->name[i])
		return (1);
	return (0);
}

int	get_cmd_len(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
