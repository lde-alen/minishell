/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 23:23:28 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_arr(t_lex *lex, t_exec *exec)
{
	init_pre_exec(lex, exec);
	if (exec->len > 1)
		loop_lst(lex, exec);
	else if (exec->len == 1)
		exec_alone(lex, exec);
	if (g_exit == -69)
		g_exit = 130;
	else if (g_exit == -1)
		g_exit = 0;
	else
	{
		if (exec->flag != 2)
		{
			exec->i = 0;
			while ((exec->i + 1) <= exec->len)
			{
				wait_stat();
				exec->i++;
			}
		}
	}
	while (lex->cmd)
		free_cmd(&lex->cmd);
}

size_t	fork_alone(t_lex *lex, t_exec *exec)
{
	ssize_t	ret;

	if (exec->flag == 1)
	{
		exec->flag = 2;
		g_exit = 0;
		exec_builtin(lex);
		free_cmd(&lex->cmd);
		if (exec->path)
			free(exec->path);
		return (1);
	}
	exec->env_kid = lst_to_char(&lex->env);
	exec->id[0] = fork();
	if (exec->id[0] < 0)
		perror("fork");
	else if (exec->id[0] == 0)
	{
		ret = main_child2(lex);
		free_child(lex);
		exit(ret);
	}
	free_env_kid(exec->env_kid);
	return (0);
}

void	exec_alone(t_lex *lex, t_exec *exec)
{
	path_check(lex, exec);
	if (lex->cmd->redir)
	{
		if (here_doc(lex, lex->cmd) == 1)
		{
			free(exec->path);
			return ;
		}
		exec->fork_id = fork();
		if (exec->fork_id == 0)
		{
			redir(lex);
			free_child(lex);
			exit(g_exit);
		}
	}
	else
		if (fork_alone(lex, exec) == 1)
			return ;
	if (exec->path)
		free(exec->path);
	init_null(lex);
}

void	loop_lst(t_lex *lex, t_exec *exec)
{
	check_path(lex->cmd, &exec);
	exec->tmp = lex->cmd;
	while (lex->cmd)
	{
		if (lex->cmd->redir)
		{
			if (here_doc(lex, exec->tmp) == 1)
			{
				lex->cmd = exec->tmp;
				return ;
			}
		}
		lex->cmd = lex->cmd->next;
	}
	lex->cmd = exec->tmp;
	while (lex->cmd)
	{
		pipe_exec(lex, exec);
		exec->i++;
		if (lex->cmd)
			free_cmd(&lex->cmd);
		exec->flag = 0;
		if (lex->cmd && lex->cmd->argument)
			check_path(lex->cmd, &exec);
	}
}

void	pipe_exec(t_lex *lex, t_exec *exec)
{
	exec->env_kid = lst_to_char(&lex->env);
	set_path(lex, exec);
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
	{
		signal(SIGQUIT, SIG_IGN);
		check_pos(lex, exec);
	}
	close_pipes(exec);
	if (exec->env_kid)
		free_env_kid(exec->env_kid);
	if (exec->path)
		free(exec->path);
	init_null(lex);
}
