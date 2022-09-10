/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/10 19:55:23 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	exec->env_kid = lst_to_char(&lst);
	exec->path = check_access(lst, cmd_lst); 
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
	// free_cmd(&cmd_lst);
	if (exec->env_kid)
		free_env_kid(exec->env_kid);
	if (exec->path)
		free(exec->path);
}

void	fork_arr(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	exec->i = 0;
	exec->flag = 0;
	exec->len = get_cmd_len(cmd_lst);
	exec->path = check_access(lst, cmd_lst);
	check_path(cmd_lst, &exec);
	if (exec->len > 1)
		loop_lst(lst, &cmd_lst, exec);
	else
		exec_alone(cmd_lst, lst, exec);
	if (exec->flag != 2)
	{
		exec->i = 0;
		while ((exec->i + 1) <= exec->len)
		{
			wait(&g_exit);
			if (WIFEXITED(g_exit))
				g_exit = WEXITSTATUS(g_exit);
			exec->i++;
		}
	}
}

void	loop_lst(t_env *lst, t_cmd **cmd_lst, t_exec *exec)
{
	free(exec->path);
	exec->path = check_access(lst, *cmd_lst);
	check_path(*cmd_lst, &exec);
	while (*cmd_lst != NULL)
	{
		if (exec->path)
			free(exec->path);
		pipe_exec(lst, *cmd_lst, exec);
		exec->i++;
		free_cmd(cmd_lst);
		if (*cmd_lst != NULL)
		{
			exec->path = check_access(lst, *cmd_lst);
			check_path(*cmd_lst, &exec);
		}
		exec->flag = 0;
	}
	//free_cmd(cmd_lst);
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
