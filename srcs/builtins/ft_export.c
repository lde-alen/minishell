/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/24 07:03:39 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void div_env(char *str, t_env *lst)
{
	char	*env_name;
	char	*env_value;
	char	*div;

	if (ft_strchr(str, '=') == NULL)
	{
		env_name = str;
		env_value = NULL;
	}
	else
	{
		env_name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
		div = ft_strchr(str, '=');
		env_value = ft_strchr(div, div[1]);
	}
	lst = push_env(lst, env_name, env_value);
	// free(env_name);
}

static t_env	*check_exist(t_env *lst, char *str)
{
	int		len;
	t_env	*tmp;
	char	*env_name;
	char	*check;

	tmp = lst;
	if (ft_strchr(str, '=') == NULL)
		env_name = str;
	else
	{
		check = ft_strchr(str, '+');
		if (check != NULL && check[1] == '=')
			len = ft_strlen(str) - ft_strlen(ft_strchr(str, '+'));
		else
			len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
		env_name = ft_substr(str, 0, len);
	}
	while (lst->next != tmp)
	{
		if (strcmp(env_name, lst->name) == 0)
		{
			free(env_name);
			return (lst);
		}
		lst = lst->next;
	}
	if (strcmp(env_name, lst->name) == 0)
	{
		free(env_name);
		return (lst);
	}
	lst = tmp;
	// free(env_name);
	return (NULL);
}

void	ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int		i;
	char	*div;
	char	*len;
	t_env	*check;
	
	i = 0;
	while (cmd_lst->argument[i])
	{
		if (ft_strchr(cmd_lst->argument[i], '=') == NULL)
		{
			check = check_exist(lst, cmd_lst->argument[i]);
			if (check == NULL)
				div_env(cmd_lst->argument[i], lst);
		}
		else
		{
			check = check_exist(lst, cmd_lst->argument[i]);
			if (check != NULL)
			{
				len = ft_strchr(cmd_lst->argument[i], '+');
				div = ft_strchr(cmd_lst->argument[i], '=');
				check->value = ft_strchr(div, div[1]);
				if (len != NULL && len[1] == '=')
					check->value = ft_strjoin(check->value, ft_strchr(div, div[1]));
			}
			else
				div_env(cmd_lst->argument[i], lst);
		}
		i++;
	}
}

void	print_lst(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;

	while (lst->next != tmp)
	{
		if (lst->value != NULL)
			ft_printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
		else
			ft_printf("declare -x %s\n", lst->name);
		lst = lst->next;
	}
	if (lst->value != NULL)
		ft_printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
	else
		ft_printf("declare -x %s\n", lst->name);
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

t_env	*check_stack(t_env *new_node, t_env *lst)
{
	t_env	*tmp;

	tmp = new_node;
	while (new_node->next != tmp)
	{
		if (lst->name[0] < new_node->name[0])
			return (push_lst(tmp, new_node, lst->name, lst->value));
		else if (lst->name[0] == new_node->name[0])
			if (iter_diff(lst, new_node) == 1)
				return (push_lst(tmp, new_node, lst->name, lst->value));
		new_node = new_node->next;
	}
	if (lst->name[0] < new_node->name[0])
		return (push_lst(tmp, new_node, lst->name, lst->value));
	else if (lst->name[0] == new_node->name[0])
			if (iter_diff(lst, new_node) == 1)
				return (push_lst(tmp, new_node, lst->name, lst->value));
	return (push_env(tmp, lst->name, lst->value));
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
