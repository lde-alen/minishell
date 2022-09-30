/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/30 15:49:38 by asanthos         ###   ########.fr       */
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

size_t	check_delimiter(t_lex *lex)
{
	size_t	i;

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
	//changed i <= len to i < len
	while (i < len)
	{
		if ((lex->cmd->redir->flag[i] == R_REDIR && i != find_redir_in(lex, R_REDIR)) || lex->cmd->redir->flag[i] == DR_REDIR)
		{
			if (((right < -1 && i != lex->cmd->redir->right_r)
				|| (right > -1 && i != lex->cmd->redir->right_dr))
				|| !lex->cmd->command)
				open_file(lex, lex->cmd->redir->file[i], O_TRUNC | O_CREAT);
		}
		else if (lex->cmd->redir->flag[i] == L_REDIR && i != find_redir_in(lex, L_REDIR))
		{
			if ((left < -1 && i != lex->cmd->redir->left_r) || !lex->cmd->command)
				open_file(lex, lex->cmd->redir->file[i], O_TRUNC);
		}
		i++;
	}
	check_redir_type(lex);
	redirect(lex);
}

void	exec_alone(t_lex *lex, t_exec *exec)
{
	size_t	ret;
	char	*val;
	int		shl_val;

	check_path(lex->cmd, &exec);
	if (lex->cmd->command)
	{
		exec->path = check_access(lex->env, lex->cmd);
		if (ft_strcmp(exec->path, "./minishell") == 0)
		{
			ft_printf("BOOP\n");
			val = search_env(lex->env, "SHLVL")->value;
			shl_val = ft_atoi(val);
			free(val);
			if (shl_val < 0)
				val = ft_strdup("0");
			else if (shl_val <= 999)
				val = ft_itoa(shl_val + 1);
			else if (shl_val == 1000)
				val = NULL;
			else
			{
				err_msg(lex->cmd, "warning", "shell level too high, resetting to 1");
				val = ft_strdup("1");
			}
		}

	}
	if (lex->cmd->redir)
	{
		here_doc(lex);
		redir(lex);
		free_redir(lex->cmd->redir);
	}
	else
	{
		exec->env_kid = lst_to_char(&lex->env);
		if (exec->flag == 1)
		{
			exec->flag = 2;
			exec_builtin(lex);
			free_cmd(&lex->cmd);
			free_env_kid(exec->env_kid);
			if (exec->path)
				free(exec->path);
			return ;
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
