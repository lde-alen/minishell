/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/14 16:21:09 by asanthos         ###   ########.fr       */
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

static char	*check_str(char *str)
{
	size_t	j;

	j = 1;
	while (str[j])
	{
		if (ft_isalnum(str[j]) == 0
			&& (str[j] != '='))
		{
			if (str[j] == '+'
				&& str[j + 1] != '=')
			{
				g_exit = 1;
				return (str);
			}
		}
		j++;
	}
	return (NULL);
}

size_t	check_validity(char *str, int check)
{
	char	*ret;
	size_t	flag;

	g_exit = 0;
	flag = 0;
	if (str[0] != '_'
		&& (isalpha((str[0]))) == 0)
	{
		g_exit = 1;
		if (check == 1)
			export_error(str);
		flag = 1;
	}
	ret = check_str(str);
	if (ret != NULL)
		flag = 1;
	if (flag == 1)
	{
		g_exit = 1;
		return (1);
	}
	return (0);
}

void	ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int		i;
	t_env	*check;

	i = 1;
	while (cmd_lst->argument[i])
	{
		if (check_validity(cmd_lst->argument[i], 1) == 0)
		{
			if (ft_strchr(cmd_lst->argument[i], '=') == NULL)
			{
				check = check_exist(lst, cmd_lst->argument[i]);
				if (check == NULL)
					div_env(cmd_lst->argument[i], lst);
			}
			else
				check_val(lst, cmd_lst, i);
		}
		i++;
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
