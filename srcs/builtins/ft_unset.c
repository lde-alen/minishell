/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 21:46:20 by asanthos         ###   ########.fr       */
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

static char	*check_str(t_cmd *cmd_lst, size_t i)
{
	size_t	j;

	j = 1;
	while (cmd_lst->argument[i][j])
	{
		if (ft_isalnum(cmd_lst->argument[i][j]) == 0
			&& (cmd_lst->argument[i][j] != '='))
		{
			if (cmd_lst->argument[i][j] == '+'
				&& cmd_lst->argument[i][j + 1] != '=')
			{
				g_exit = 1;
				return (cmd_lst->argument[i]);
			}
		}
		j++;
	}
	return (NULL);
}

//CHECK
char	*check_validit(t_cmd *cmd_lst)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (cmd_lst->argument[i])
	{
		if (cmd_lst->argument[i][0] != '_'
			&& (isalpha((cmd_lst->argument[i][0]))) == 0)
		{
			g_exit = 1;
			return (cmd_lst->argument[i]);
		}
		ret = check_str(cmd_lst, i);
		if (ret != NULL)
			return (ret);
		i++;
	}
	g_exit = 0;
	return (NULL);
}

int	loop_arg(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	size_t	flag;

	i = 1;
	flag = 0;
	while (cmd->argument[i])
	{
		j = 0;
		if (check_validity(cmd->argument[i], 1) == 1)
		{
			flag = 1;
			err_msg(cmd->argument[i], "not a valid identifier");
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

void	ft_unset(t_env *lst, t_cmd *cmd_lst)
{
	size_t	i;
	t_env	*tmp;

	i = 1;
	if (loop_arg(cmd_lst) == 1)
		return ;
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
