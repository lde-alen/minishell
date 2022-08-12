/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:30:36 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/10 11:50:59 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*push_cmd(t_env *lst, char *env_name, char *env_value)
{
	t_env	*new_node;
	t_env	*temp_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->name = ft_strdup(env_name);
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
		new_node->prev = lst->next;
		lst->next = new_node;
		new_node->next = temp_node;
		lst = temp_node;
	}
	free(env_name);
	free(env_value);
	return (lst);
}

//just for teshtazz
void	print_list_cmd(t_cmd *head)
{
	int		i;

	i = 0;
	if (head->argument[i])
	{
		while (head->argument[i])
		{
			ft_printf("%s\n", head->argument[i]);
			i++;
		}
	}
	ft_printf("%s\n", head->command);
}

t_cmd	*ft_lst_init(char *str)
{
	char	**split_cmd;
	t_cmd   *cmd_lst;
	int		i;

	cmd_lst = (t_cmd *)malloc(sizeof(t_cmd));
	split_cmd = ft_split(str, ' ');
	i = 0;
	while (split_cmd[i])
		i++;
	//+1??
	cmd_lst->argument = (char **)ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (split_cmd[i])
	{
		cmd_lst->argument[i] = ft_strdup(split_cmd[i]);
		free(split_cmd[i]);
		i++;
	}
	cmd_lst->argument[i] = NULL;
	free(split_cmd);
	cmd_lst->command = cmd_lst->argument[0];
	return (cmd_lst);
}
