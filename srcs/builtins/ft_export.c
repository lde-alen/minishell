/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/20 16:17:26 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern int g_exit;

static void	check_val(t_env *lst, t_cmd *cmd_lst, char	*len, int i)
{
	t_env	*check;
	char	*div;
	char	*tmp;

	check = check_exist(lst, cmd_lst->argument[i]);
	if (check != NULL)
	{
		len = ft_strchr(cmd_lst->argument[i], '+');
		div = ft_strchr(cmd_lst->argument[i], '=');
		if (len != NULL && len[1] == '=')
		{
			if (check->value != NULL)
			{
				tmp = ft_strdup(check->value);
				free(check->value);
				check->value = ft_strjoin(tmp, ft_strchr(div, div[1]));
				free(tmp);
			}
			else
				check->value = ft_strdup(ft_strchr(div, div[1]));
		}
		else
		{
			if (check->value)
				free(check->value);
			check->value = ft_strdup(ft_strchr(div, div[1]));
		}
	}
	else
		div_env(cmd_lst->argument[i], lst);
}


//CHECK
static char	*check_validity(t_cmd *cmd_lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_lst->argument[i])
	{
		if (cmd_lst->argument[i][0] != '_' && (isalpha((cmd_lst->argument[i][0]))) == 0)
		{
			// g_exit = 1;
			return (cmd_lst->argument[i]);
		}
		j = 1;
		while (cmd_lst->argument[i][j])
		{
			if (ft_isalnum(cmd_lst->argument[i][j]) == 0 && (cmd_lst->argument[i][j] != '='))
			{
				if (cmd_lst->argument[i][j] == '+' && cmd_lst->argument[i][j + 1] != '=')
					return (cmd_lst->argument[i]);
				// g_exit = 1;
			}
			j++;
		}
		i++;
	}
	// g_exit = 0;
	return (NULL);
}

void	ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int		i;
	char	*len;
	char	*val;
	t_env	*check;

	i = 1;
	len = NULL;
	val = check_validity(cmd_lst);
	if (val != NULL)
		export_error(val);
	else
	{
		// VALGRIND_DO_LEAK_CHECK;
		while (cmd_lst->argument[i])
		{
			if (ft_strchr(cmd_lst->argument[i], '=') == NULL)
			{
				check = check_exist(lst, cmd_lst->argument[i]);
				if (check == NULL)
					div_env(cmd_lst->argument[i], lst);
			}
			else
				check_val(lst, cmd_lst, len, i);
			i++;
		}
	}
}

void	lonely_export(t_env *lst)
{
	t_env	*new_node;
	t_env	*tmp;

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

//export boop test test=lala lala=hah lala+=ye
//test with ^^

//valgrind do_leak_check
