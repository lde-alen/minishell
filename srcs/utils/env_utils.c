/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:08:44 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/09 15:17:33 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->export_flag = 0;
	new_node->name = ft_strdup(env_name);
	new_node->value = ft_strdup(env_value);
	lst->prev->next = new_node;
	new_node->prev = lst->prev;
	lst->prev = new_node;
	new_node->next = lst;
	if (new == lst)
		return (new_node);
	return (new);
}

t_env	*push_env(t_env *lst, char *env_name, char *env_value)
{
	t_env	*new_node;
	t_env	*temp_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->name = ft_strdup(env_name);
	if (env_value)
		new_node->value = ft_strdup(env_value);
	if (!lst)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		lst = new_node;
	}
	else
	{
		temp_node = lst;
		while (lst->next != temp_node)
			lst = lst->next;
		lst->next = new_node;
		new_node->prev = lst;
		lst = temp_node;
		lst->prev = new_node;
		new_node->next = lst;
	}
	return (lst);
}
