/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:46:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/25 17:48:01 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_builtin(t_cmd *cmd_lst)
{
	if (cmd_lst->command[0] == '$' || ft_strcmp(cmd_lst->command, "echo") == 0
		|| ft_strcmp(cmd_lst->command, "pwd") == 0
		|| ft_strcmp(cmd_lst->command, "env") == 0
		|| (ft_strcmp(cmd_lst->command, "export") == 0
			&& cmd_lst->argument[1] != NULL)
		|| ft_strcmp(cmd_lst->command, "export") == 0
		|| ft_strcmp(cmd_lst->command, "unset") == 0
		|| ft_strcmp(cmd_lst->command, "cd") == 0
		|| ft_strcmp(cmd_lst->command, "exit") == 0)
		return (1);
	return (0);
}

size_t	check_path(t_cmd *cmd_lst, t_exec **exec)
{
	if ((*exec)->path == NULL)
	{
		if (check_builtin(cmd_lst) == 0)
		{
			perror("path error");
			free((*exec)->path);
			return (1);
		}
		else
			(*exec)->flag = 1;
		free((*exec)->path);
	}
	return (0);
}

size_t	check_all_path(t_env *lst, t_cmd *cmd_lst)
{
	char	*path;

	while (cmd_lst != NULL)
	{
		path = check_access(lst, cmd_lst);
		if (path == NULL)
		{
			if (check_builtin(cmd_lst) == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd_lst->argument[0], 2);
				ft_putendl_fd(": command not found\n", 2);
				return (1);
			}
		}
		free(path);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}
