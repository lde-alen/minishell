/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 20:54:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_arr(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	exec->i = 0;
	exec->flag = 0;
	exec->len = get_cmd_len(cmd_lst);
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

void	exec_alone(t_cmd *cmd_lst, t_env *lst, t_exec *exec)
{
	size_t	ret;

	exec->path = check_access(lst, cmd_lst);
	if (exec_builtin(lst, cmd_lst) == 0)
	{
		exec->flag = 2;
		free(exec->path);
		free_cmd(&cmd_lst);
		return ;
	}
	exec->env_kid = lst_to_char(&lst);
	exec->id[0] = fork();
	if (exec->id[0] < 0)
		perror("fork");
	else if (exec->id[0] == 0)
	{
		ret = main_child2(cmd_lst, exec);
		free_child(exec, lst, cmd_lst);
		exit (ret);
	}
	free(exec->path);
	free_env_kid(exec->env_kid);
	free_cmd(&cmd_lst);
}

void	loop_lst(t_env *lst, t_cmd **cmd_lst, t_exec *exec)
{
	while (*cmd_lst != NULL)
	{
		pipe_exec(lst, *cmd_lst, exec);
		exec->i++;
		if (*cmd_lst)
			free_cmd(cmd_lst);
		if (*cmd_lst)
			check_path(*cmd_lst, &exec);
		exec->flag = 0;
	}
}

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
	if (exec->env_kid)
		free_env_kid(exec->env_kid);
	if (exec->path)
		free(exec->path);
}
