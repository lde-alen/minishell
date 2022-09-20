/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/20 04:13:12 by asanthos         ###   ########.fr       */
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
	else if (exec->len == 1 && lex->cmd->command)
		exec_alone(lex, exec);
	else
	{
		exec->flag = 2;
		redir(lex, exec);
	}
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

void	redir(t_lex *lex, t_exec *exec)
{
	ssize_t	i;
	ssize_t	len;
	ssize_t	right;
	ssize_t	left;

	i = 0;
	len = lex->cmd->redir->flag_len;
	lex->cmd->redir->left_r = find_redir_in(lex, L_REDIR);
	lex->cmd->redir->left_dr = find_redir_in(lex, DL_REDIR);
	lex->cmd->redir->right_r = find_redir_in(lex, R_REDIR);
	lex->cmd->redir->right_dr = find_redir_in(lex, DR_REDIR);
	left = lex->cmd->redir->left_r - lex->cmd->redir->left_dr;
	right = lex->cmd->redir->right_r - lex->cmd->redir->right_dr;
	while (i < len && lex->cmd->redir->flag[len - 1] == DL_REDIR)
		len--;
	while (i < len && (i + 1) != len)
	{
		if (lex->cmd->redir->flag[i] == R_REDIR || lex->cmd->redir->flag[i] == DR_REDIR)
		{
			if ((right < -1 && i != lex->cmd->redir->right_r)
				|| (right > -1 && i != lex->cmd->redir->right_dr))
				open_file(lex->cmd->redir->file[i], O_TRUNC | O_CREAT);
			// lex->cmd->redir->flag[i] = NOTHING;
		}
		else if (lex->cmd->redir->flag[i] == L_REDIR)
		{
			// if (find_redir_in(lex, L_REDIR) != lex->cmd->redir->file[i])
				// lex->cmd->redir->flag[i] = NOTHING;
			if (left < -1 && i != lex->cmd->redir->left_r)
				open_file(lex->cmd->redir->file[i], O_TRUNC);
		}
		i++;
	}
	// if (check_delimiter(lex) == 1)
		here_doc(lex, exec);
}

void	exec_alone(t_lex *lex, t_exec *exec)
{
	size_t	ret;

	check_path(lex->cmd, &exec);
	exec->path = check_access(lex->env, lex->cmd);
	if (lex->cmd->redir)
		redir(lex, exec);
	else
	{
		exec->env_kid = lst_to_char(&lex->env);
		exec->id[0] = fork();
		if (exec->id[0] < 0)
			perror("fork");
		else if (exec->id[0] == 0)
		{
			ret = main_child2(lex->env, lex->cmd, exec);
			free_child(exec, lex);
			exit (ret);
			exit(0);
		}
		free(exec->path);
		free_env_kid(exec->env_kid);
		free_cmd(&lex->cmd);
	}
}

void	loop_lst(t_lex *lex, t_exec *exec)
{
	check_path(lex->cmd, &exec);
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
