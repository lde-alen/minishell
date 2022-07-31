/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:18:14 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 07:43:11 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_env	*ft_env(char **env)
{
	t_env	*lst;
	char	*env_name;
	char	*env_value;
	char	*div;
	int		i;

	i = 0;
	lst = NULL;
	while (env[i])
	{
		env_name = ft_substr(env[i], 0, ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		div = ft_strchr(env[i], '=');
		env_value = ft_strchr(div, div[1]);
		lst = push_env(lst, env_name, env_value);
		free(env_name);
		i++;
	}
	return (lst);
}
