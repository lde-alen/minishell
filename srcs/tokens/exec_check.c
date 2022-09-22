/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:46:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/22 19:50:14 by asanthos         ###   ########.fr       */
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
	if (cmd_lst->command)
	{
		if (check_builtin(cmd_lst) == 1)
			(*exec)->flag = 1;
	}
}

void	pipe_arr(t_exec *exec)
{
	if (pipe(exec->fd[exec->i]) < 0)
	{
		if (exec->i != 0)
		{
			close(exec->fd[exec->i - 1][0]);
			close(exec->fd[exec->i - 1][1]);
		}
		perror("pipe");
	}
}

void	close_pipes(t_exec *exec)
{
	if (exec->i == 0)
		close(exec->fd[exec->i][1]);
	else if ((exec->i + 1) == exec->len)
		close(exec->fd[exec->i - 1][0]);
	else
	{
		close(exec->fd[exec->i - 1][0]);
		close(exec->fd[exec->i][1]);
	}
}
