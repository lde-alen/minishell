/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 16:11:33 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_arr(t_lex *lex, t_exec *exec)
{
	exec->i = 0;
	exec->flag = 0;
	exec->len = get_cmd_len(lex->cmd);
	if (exec->len > 1)
		loop_lst(lex, exec);
	else if (exec->len == 1)
		exec_alone(lex, exec);
	if (exec->flag != 2)
	{
		exec->i = 0;
		while ((exec->i + 1) <= exec->len)
		{
			wait(&g_exit);
			if (WIFEXITED(g_exit))
			{
				ft_printf("G_exit: %d\n", g_exit);
				g_exit = WEXITSTATUS(g_exit);
			}
			exec->i++;
		}
	}
}

size_t	fork_alone(t_lex *lex, t_exec *exec)
{
	ssize_t	ret;

	exec->env_kid = lst_to_char(&lex->env);
	if (exec->flag == 1)
	{
		exec->flag = 2;
		exec_builtin(lex);
		free_cmd(&lex->cmd);
		free_env_kid(exec->env_kid);
		if (exec->path)
			free(exec->path);
		return (1);
	}
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
	check_path(lex->cmd, &exec);
	if (lex->cmd->command)
	{
		exec->path = check_access(lex->env, lex->cmd);
		set_shlvl(lex, exec);
	}
	if (lex->cmd->redir)
	{
		here_doc(lex);
		redir(lex);
		free_redir(lex->cmd->redir);
	}
	else
	{
		if (fork_alone(lex, exec) == 1)
			return ;
	}
	if (exec->path)
		free(exec->path);
	free_cmd(&lex->cmd);
}

void	loop_lst(t_lex *lex, t_exec *exec)
{
	t_cmd	*tmp;

	check_path(lex->cmd, &exec);
	tmp = lex->cmd;
	while (lex->cmd != NULL)
	{
		if (lex->cmd->redir)
			here_doc(lex);
		lex->cmd = lex->cmd->next;
	}
	lex->cmd = tmp;
	while (lex->cmd != NULL)
	{
		pipe_exec(lex, exec);
		exec->i++;
		if (lex->cmd)
		{
			if (lex->cmd->redir)
				free_redir(lex->cmd->redir);
			free_cmd(&lex->cmd);
		}
		exec->flag = 0;
		if (lex->cmd)
			check_path(lex->cmd, &exec);
	}
}

void	pipe_exec(t_lex *lex, t_exec *exec)
{
	exec->env_kid = lst_to_char(&lex->env);
	if (lex->cmd->argument)
		exec->path = check_access(lex->env, lex->cmd);
	else
		exec->path = NULL;
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
