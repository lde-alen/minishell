/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:25:19 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 20:38:28 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_lst_len(t_env *env)
{
	t_env	*tmp;
	size_t	i;

	i = 0;
	tmp = env;
	while(env->next != tmp)
	{
		i++;
		env = env->next;
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

size_t	get_cmd_len(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
