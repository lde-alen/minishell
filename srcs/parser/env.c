/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:08:44 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/11 13:58:54 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->name = ft_strdup(env_name);
	new_node->value = env_value;
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
	new_node->value = env_value;
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
