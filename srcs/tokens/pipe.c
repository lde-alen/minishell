/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/31 10:32:21 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	if ((exec->i + 1) != exec->len)
		pipe_arr(exec);
	exec->id[exec->i] = fork();
	if (exec->id[exec->i] < 0)
	{
		close_pipes(exec);
		perror("Fork");
		return ;
	}
	else if (exec->id[exec->i] == 0)
		check_pos(lst, cmd_lst, exec);
	close_pipes(exec);
}

void	fork_arr(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	exec->i = 0;
	exec->flag = 0;
	exec->len = get_cmd_len(cmd_lst);
	exec->path = check_access(lst, cmd_lst);
	if (check_path(cmd_lst, &exec) == 1)
		return ;
	free(exec->path);
	if (exec->len > 1)
		loop_lst(lst, &cmd_lst, exec);
	else
		exec_alone(cmd_lst, lst, exec);
	if (exec->flag == 2)
	{
		exec->i = 0;
		while ((exec->i + 1) <= exec->len)
		{
			wait(&exec->status);
			g_exit = WEXITSTATUS(exec->status);
			g_exit = 126;
			ft_printf("ME: %d\n", g_exit);
			exec->i++;
		}
	}
}

void	loop_lst(t_env *lst, t_cmd **cmd_lst, t_exec *exec)
{
	exec->path = check_access(lst, *cmd_lst);
	if (check_path(*cmd_lst, &exec) == 1)
		return ;
	while (*cmd_lst != NULL)
	{
		pipe_exec(lst, *cmd_lst, exec);
		exec->i++;
		free(exec->path);
		free_cmd(cmd_lst);
		if (*cmd_lst != NULL)
		{
			exec->path = check_access(lst, *cmd_lst);
			if (check_path(*cmd_lst, &exec) == 1)
				return ;
		}
	}
	if (*cmd_lst && exec->path == NULL)
		ft_putendl_fd("path doesn't exist", 2);
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
