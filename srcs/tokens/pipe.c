/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/13 04:52:50 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_arr(t_lex *lex, t_exec *exec)
{
	exec->i = 0;
	exec->flag = 0;
	exec->len = get_cmd_len(lex->cmd);
	check_path(lex->cmd, &exec);
	if (exec->len > 1)
		loop_lst(lex, exec);
	else
		exec_alone(lex, exec);
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

void	exec_alone(t_lex *lex, t_exec *exec)
{
	size_t	ret;

	exec->path = check_access(lex->env, lex->cmd);
	if (exec_builtin(lex->env, lex->cmd) == 0)
	{
		exec->flag = 2;
		free(exec->path);
		free_cmd(&lex->cmd);
		return ;
	}
	exec->env_kid = lst_to_char(&lex->env);
	exec->id[0] = fork();
	if (exec->id[0] < 0)
		perror("fork");
	else if (exec->id[0] == 0)
	{
		ret = main_child2(lex->cmd, exec);
		free_child(exec, lex);
		exit (ret);
	}
	free(exec->path);
	free_env_kid(exec->env_kid);
	free_cmd(&lex->cmd);
}

void	loop_lst(t_lex *lex, t_exec *exec)
{
	while (lex->cmd != NULL)
	{
		pipe_exec(lex, exec);
		exec->i++;
		if (lex->cmd)
			free_cmd(&lex->cmd);
		if (lex->cmd)
			check_path(lex->cmd, &exec);
		exec->flag = 0;
	}
}

void	pipe_exec(t_lex *lex, t_exec *exec)
{
	exec->env_kid = lst_to_char(&lex->env);
	exec->path = check_access(lex->env, lex->cmd);
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
		check_pos(lex, exec);
	close_pipes(exec);
	if (exec->env_kid)
		free_env_kid(exec->env_kid);
	if (exec->path)
		free(exec->path);
}
