/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 21:52:54 by asanthos         ###   ########.fr       */
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
	while (j < ft_strlen(str))
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
	size_t	i;

	(void)check;
	g_exit = 0;
	flag = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (i < 0 && ft_isdigit(str[i]))
				break ;
			g_exit = 1;
			flag = 1;
		}
		i++;
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
	if (loop_arg(cmd_lst) == 1)
		return ;
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
