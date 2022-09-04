/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:46:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/04 11:40:09 by asanthos         ###   ########.fr       */
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

void	check_path(t_cmd *cmd_lst, t_exec **exec)
{
	if (check_builtin(cmd_lst) == 1)
		(*exec)->flag = 1;
}

size_t	check_all_path(t_env *lst, t_cmd *cmd_lst)
{
	struct stat	path_stat;
	char		*path;

	while (cmd_lst != NULL)
	{
		if (check_builtin(cmd_lst) == 0)
		{
			path = check_access(lst, cmd_lst);
			stat(cmd_lst->command, &path_stat);
			if (S_ISDIR(path_stat.st_mode))
			{
				if (cmd_lst->command[get_len(cmd_lst->command) - 1] != '/'
					&& ft_strncmp(cmd_lst->command, "./", 2) != 0)
					path = NULL;
				else
				{
					err_msg(cmd_lst, "", "Is a directory");
					g_exit = 126;
					return (1);
				}
			}
			if (path == NULL)
			{
				if (cmd_lst->command[get_len(cmd_lst->command) - 1] == '/')
				{
					err_msg(cmd_lst, "", "Not a directory");
					g_exit = 126;
					return (1);
				}
				else if (ft_strncmp(cmd_lst->command, "./", 2) == 0)
				{
					err_msg(cmd_lst, "", "Permission denied");
					g_exit = 126;
					return (1);
				}
				err_msg(cmd_lst, "", "command not found");
				g_exit = 127;
				return (1);
			}
		}
		cmd_lst = cmd_lst->next;
	}
	return (0);
}
