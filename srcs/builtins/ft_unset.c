/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/16 19:11:13 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ch_equality(char *str, t_env *lst)
{
	t_env	*tmp2;

	// ft_printf("STR: %s\n", str);
	// ft_printf("Name: %s\n", lst->name);
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

int	loop_arg(char *str)
{
	size_t	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '=')
		{
			err_msg(str, ": not a valid identifier");
			g_exit = 1;
			return (1);
		}
		j++;
	}
	if (check_validity(str, 1) == 1)
		return (1);
	return (0);
}

void	ft_unset(t_env *lst, t_cmd *cmd_lst)
{
	size_t	i;
	t_env	*tmp;

	i = 1;
	while (cmd_lst->argument[i])
	{
		if (loop_arg(cmd_lst->argument[i]) == 0)
		{
			tmp = lst;
			if (ch_equality(cmd_lst->argument[i], tmp) == 1)
				break ;
			while (tmp->next != lst)
			{
				if (ch_equality(cmd_lst->argument[i], tmp) == 1)
					break ;
				tmp = tmp->next;
			}
		}
		i++;
	}
}
