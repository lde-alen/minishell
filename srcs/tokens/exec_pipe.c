/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/25 18:02:01 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_child2(t_cmd *cmd_lst, t_exec *exec)
{
	if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static	void	first_child(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(exec->fd[exec->i][1]);
	if (exec->flag == 1)
		exec_builtin(lst, cmd_lst);
	else
	{
		if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
			perror("Execve problem");
	}
	exit(0);
}

static	void	last_child(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(exec->fd[(exec->i - 1)][0]);
	if (exec->flag == 1)
		exec_builtin(lst, cmd_lst);
	else
	{
		if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
			perror("Execve problem");
	}
	exit(0);
}

static	void	mid_kid(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(exec->fd[(exec->i - 1)][0]);
	close(exec->fd[exec->i][1]);
	if (exec->flag == 1)
		exec_builtin(lst, cmd_lst);
	else
	{
		if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
			perror("Execve problem");
	}
	exit(0);
}

void	check_pos(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	exec->env_kid = lst_to_char(lst);
	exec->path = check_access(lst, cmd_lst);
	if (exec->i == 0)
		first_child(lst, cmd_lst, exec);
	else if (exec->i + 1 == exec->len)
		last_child(lst, cmd_lst, exec);
	else
		mid_kid(lst, cmd_lst, exec);
	free(exec->path);
	free_cmd(&cmd_lst);
	free_env_kid(exec->env_kid);
}
