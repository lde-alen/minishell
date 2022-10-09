/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/09 14:19:29 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ch_equality(char *str, t_env *lst)
{
	t_env	*tmp2;

	if (ft_strcmp(str, lst->name) == 0)
	{
		tmp2 = lst;
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
		free(tmp2->name);
		free(tmp2->value);
		free(tmp2);
		return (1);
	}
	return (0);
}

int	loop_arg(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	*val;

	i = 0;
	while (cmd->argument[i])
	{
		j = 0;
		while (cmd->argument[i][j])
		{
			if (cmd->argument[i][j] == '=')
			{
				err_msg(cmd->argument[i], ": not a valid identifier");
				g_exit = 1;
				return (1);
			}
			j++;
		}
		i++;
	}
	val = check_validity(cmd);
	if (val != NULL)
		err_msg(val, ": not a valid identifier");
	return (0);
}

void	ft_unset(t_env *lst, t_cmd *cmd_lst)
{
	size_t	i;
	t_env	*tmp;

	if (loop_arg(cmd_lst) == 1)
		return ;
	i = 1;
	while (cmd_lst->argument[i])
	{
		tmp = lst;
		while (tmp->next != lst)
		{
			if (ch_equality(cmd_lst->argument[i], tmp) == 1)
				break ;
			tmp = tmp->next;
		}
		ch_equality(cmd_lst->argument[i], tmp);
		i++;
	}
}
