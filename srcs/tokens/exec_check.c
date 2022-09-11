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
