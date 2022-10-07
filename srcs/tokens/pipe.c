/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/07 11:46:03 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_arr(t_lex *lex, t_exec *exec)
{
	t_cmd	*tmp;

	exec->i = 0;
	exec->flag = 0;
	exec->len = get_cmd_len(lex->cmd);
	tmp = lex->cmd;
	while (lex->cmd)
	{
		if (lex->cmd->redir)
			ft_redir_init(lex);
		lex->cmd = lex->cmd->next;
	}
	lex->cmd = tmp;
	if (exec->len > 1)
		loop_lst(lex, exec);
	else if (exec->len == 1)
		exec_alone(lex, exec);
	if (exec->flag != 2)
	{
		exec->i = 0;
		while ((exec->i + 1) <= exec->len)
		{
			signal(SIGINT, SIG_IGN);
			wait(&g_exit);
			signal(SIGINT, sig_handler);
			if (WIFEXITED(g_exit))
			{
				ft_printf("G_exit: %d\n", g_exit);
				g_exit = WEXITSTATUS(g_exit);
			}
			exec->i++;
		}
	}
	while (lex->cmd)
		free_cmd(lex, &lex->cmd);
}

size_t	fork_alone(t_lex *lex, t_exec *exec)
{
	ssize_t	ret;

	exec->env_kid = lst_to_char(&lex->env);
	if (exec->flag == 1)
	{
		exec->flag = 2;
		exec_builtin(lex);
		free_cmd(lex, &lex->cmd);
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
		// ft_redir_init(lex);
		int id = fork();
		if (id == 0)
		{
			here_doc(lex);
			redir(lex);
			// free_redir(lex->cmd->redir);
			free_child(lex);
			exit(0);
		}
		signal(SIGINT, SIG_IGN);
		wait(NULL);
		signal(SIGINT, sig_handler);
	}
	else
	{
		if (fork_alone(lex, exec) == 1)
			return ;
	}
	if (exec->path)
		free(exec->path);
	// free_cmd(lex, &lex->cmd);
	// lex->cmd = NULL;
	init_null(lex);
}

void	loop_lst(t_lex *lex, t_exec *exec)
{
	t_cmd	*tmp;
	int		id;

	check_path(lex->cmd, &exec);
	tmp = lex->cmd;
	id = fork();
	if (id == 0)
	{
		while (lex->cmd != NULL)
		{
			if (lex->cmd->redir)
			{
				// ft_redir_init(lex);
				here_doc(lex);
			}
			lex->cmd = lex->cmd->next;
		}
		lex->cmd = tmp;
		while (lex->cmd != NULL)
		{
			pipe_exec(lex, exec);
			exec->i++;
			if (lex->cmd)
				free_cmd(lex, &lex->cmd);
			exec->flag = 0;
			if (lex->cmd && lex->cmd->argument)
				check_path(lex->cmd, &exec);
			init_null(lex);
		}
		free_child(lex);
		exit(0);
	}
	// while (lex->cmd)
	// 	free_cmd(lex, &lex->cmd);
}

void	pipe_exec(t_lex *lex, t_exec *exec)
{
	exec->env_kid = lst_to_char(&lex->env);
	if (lex->cmd->argument)
	{
		if (lex->cmd->argument[0])
			exec->path = check_access(lex->env, lex->cmd);
		else
			exec->path = NULL;
	}
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
	signal(SIGINT, SIG_IGN);
	wait(NULL);
	signal(SIGINT, sig_handler);
	init_null(lex);
}
