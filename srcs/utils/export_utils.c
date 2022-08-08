/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:11:19 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 16:14:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//assign export info to variables
void	div_env(char *str, t_env *lst)
{
	char	*env_name;
	char	*env_value;
	char	*div;

	if (ft_strchr(str, '=') == NULL)
	{
		env_name = ft_strdup(str);
		env_value = NULL;
	}
	else
	{
		env_name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
		div = ft_strchr(str, '=');
		env_value = ft_strchr(div, div[1]);
	}
	lst = push_env(lst, env_name, env_value);
	free(env_name);
}

static	t_env	*find_var(t_env *lst, char *env_name)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (ft_strcmp(env_name, lst->name) == 0)
		{
			free(env_name);
			return (lst);
		}
		lst = lst->next;
	}
	if (ft_strcmp(env_name, lst->name) == 0)
	{
		free(env_name);
		return (lst);
	}
	lst = tmp;
	free(env_name);
	return (NULL);
}

//check whether the variable exists
t_env	*check_exist(t_env *lst, char *str)
{
	int		len;
	char	*env_name;
	char	*check;
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
	return (find_var(lst, env_name));
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
