/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:30:36 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/26 12:12:05 by asanthos         ###   ########.fr       */
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

void	split_lst_cmd(char **split_cmd, t_cmd **cmd_lst, size_t i)
{
	while (split_cmd[i])
	{
		(*cmd_lst)->argument[i] = ft_strdup(split_cmd[i]);
		free(split_cmd[i]);
		i++;
	}
	(*cmd_lst)->argument[i] = NULL;
	free(split_cmd);
	(*cmd_lst)->command = (*cmd_lst)->argument[0];
	(*cmd_lst)->next = NULL;
}

t_cmd	*ft_lst_init(t_cmd *cmd, char *str)
{
	char	**split_cmd;
	t_cmd	*cmd_lst;
	t_cmd	*tmp;
	size_t	i;

	cmd_lst = (t_cmd *)malloc(sizeof(t_cmd));
	split_cmd = ft_split(str, ' ');
	i = 0;
	while (split_cmd[i])
		i++;
	cmd_lst->argument = (char **)ft_calloc((i + 1), sizeof(char *));
	i = 0;
	split_lst_cmd(split_cmd, &cmd_lst, i);
	if (!cmd)
		return (cmd_lst);
	tmp = cmd;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = cmd_lst;
	return (cmd);
}

t_cmd	*ft_cmd_lst(char *str)
{
	char	**split_pipes;
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	split_pipes = ft_split(str, '|');
	while (split_pipes[i])
	{
		cmd = ft_lst_init(cmd, split_pipes[i]);
		free(split_pipes[i]);
		i++;
	}
	free(split_pipes[i]);
	free(split_pipes);
	return (cmd);
}
