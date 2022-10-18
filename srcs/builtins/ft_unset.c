/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/19 01:50:49 by asanthos         ###   ########.fr       */
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

void	ft_unset(t_env *lst, t_cmd *cmd_lst)
{
	size_t	i;
	t_env	*tmp;

	i = 1;
	while (cmd_lst->argument[i])
	{
		tmp = lst;
		if (check_validity(cmd_lst->argument[i]) == 0)
		{
			while (tmp->next != lst)
			{
				if (ch_equality(cmd_lst->argument[i], tmp) == 1)
					break ;
				tmp = tmp->next;
			}
			ch_equality(cmd_lst->argument[i], tmp);
		}
		else
			err_msg(cmd_lst->argument[i], "not a valid identifier");
		i++;
	}
}
