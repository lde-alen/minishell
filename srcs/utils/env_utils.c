/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:08:44 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 19:35:06 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//assign export info to variables
void	div_env(char *str, t_env *lst)
{
	char	*env_name;
	char	*env_value;
	char	*store;

	if (ft_strchr(str, '=') == NULL)
	{
		env_name = ft_strdup(str);
		env_value = NULL;
	}
	else
		get_sub(&store, str, &env_name, &env_value);
	lst = push_env(lst, env_name, env_value);
	free(env_name);
	if (env_value)
		free(env_value);
}

t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->name = ft_strdup(env_name);
	if (env_value)
		new_node->value = ft_strdup(env_value);
	else
		new_node->value = NULL;
	lst->prev->next = new_node;
	new_node->prev = lst->prev;
	lst->prev = new_node;
	new_node->next = lst;
	if (new == lst)
		return (new_node);
	return (new);
}

void	add_to_lst(t_env **lst, t_env **temp_node, t_env **new_node)
{
	*temp_node = *lst;
	while ((*lst)->next && (*lst)->next != *temp_node)
		*lst = (*lst)->next;
	(*lst)->next = *new_node;
	(*new_node)->prev = *lst;
	*lst = *temp_node;
	(*lst)->prev = *new_node;
	(*new_node)->next = *lst;
}

t_env	*push_env(t_env *lst, char *env_name, char *env_value)
{
	t_env	*new_node;
	t_env	*temp_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	ft_env_init(new_node);
	new_node->name = ft_strdup(env_name);
	new_node->value = NULL;
	if (env_value)
		new_node->value = ft_strdup(env_value);
	if (!lst)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		lst = new_node;
	}
	else
		add_to_lst(&lst, &temp_node, &new_node);
	return (lst);
}

t_env	*search_env(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp->next != lst)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->name, str) == 0)
		return (tmp);
	return (NULL);
}
