/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/15 12:43:54 by asanthos         ###   ########.fr       */
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

void	check_redir(t_lex *lex, size_t len)
{
	if (lex->cmd->redir->flag[len] == R_REDIR)
		redirect_out(lex->env, lex->cmd);
	else if (lex->cmd->redir->flag[len] == L_REDIR)
		redirect_in(lex->env, lex->cmd);
	else if (lex->cmd->redir->flag[len] == DR_REDIR)
		append_out(lex->env, lex->cmd);
	lex->cmd->redir->flag[len] = NOTHING;
}

size_t	check_delimiter(t_lex *lex)
{
	size_t i;

	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] != NOTHING)
			return (1);
		i++;
	}
	return (0);
}

void	redir(t_lex *lex)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = lex->cmd->redir->flag_len - 1;
	while (lex->cmd->redir->flag[len] == DL_REDIR)
		len--;
	while (i <= len)
	{
		if (lex->cmd->redir->flag[i] == R_REDIR || lex->cmd->redir->flag[i] == DR_REDIR)
		{
			open_file(lex->cmd->redir->file[i], O_TRUNC | O_CREAT);
			lex->cmd->redir->flag[i] = NOTHING;
		}
		else if (lex->cmd->redir->flag[i] == R_REDIR)
		{
			open_file(lex->cmd->redir->file[i], O_TRUNC);
			lex->cmd->redir->flag[i] = NOTHING;
		}
		i++;
	}
	if (check_delimiter(lex) == 1)
		here_doc(lex);
	check_redir(lex, len);
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
		if (lex->cmd->redir->flag_len > 0)
			redir(lex);
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
		exec->flag = 0;
		if (lex->cmd)
			check_path(lex->cmd, &exec);
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
