/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/13 20:02:49 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_val(t_env *lst, t_cmd *cmd_lst, int i)
{
	t_env	*check;

	check = check_exist(lst, cmd_lst->argument[i]);
	if (check != NULL)
		join_str(cmd_lst, i, &check);
	else
		div_env(cmd_lst->argument[i], lst);
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
char	*check_validity(t_cmd *cmd_lst)
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

char	*check_validity(t_cmd *cmd_lst)
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
			export_error(cmd_lst->argument[i]);
			// return (cmd_lst->argument[i]);
		}
		ret = check_str(cmd_lst, i);
		if (ret != NULL)
			return (ret);
		i++;
	}
	g_exit = 0;
	return (NULL);
}

void	ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int		i;
	char	*val;
	t_env	*check;

	i = 1;
	val = check_validity(cmd_lst);
	if (val != NULL)
		export_error(val);
	else
	{
		while (cmd_lst->argument[i])
		{
			if (ft_strchr(cmd_lst->argument[i], '=') == NULL)
			{
				check = check_exist(lst, cmd_lst->argument[i]);
				if (check == NULL)
					div_env(cmd_lst->argument[i], lst);
			}
			else
				check_val(lst, cmd_lst, i);
			i++;
		}
	}
}

void	lonely_export(t_env *lst)
{
	t_env	*new_node;
	t_env	*tmp;

	g_exit = 0;
	tmp = lst;
	new_node = NULL;
	while (lst->next != tmp)
	{
		if (!new_node)
			new_node = push_env(new_node, lst->name, lst->value);
		else
			new_node = check_stack(new_node, lst);
		lst = lst->next;
	}
	new_node = check_stack(new_node, lst);
	print_lst(new_node);
	free_env_lst(new_node);
}
