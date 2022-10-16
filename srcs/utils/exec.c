/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/16 13:29:54 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	exec_builtin(t_lex *lex)
{
	if (lex->cmd->command[0] == '$')
		ft_expander(lex->env, lex->cmd->command);
	else if (ft_strcmp(lex->cmd->command, "echo") == 0)
		ft_echo(lex->cmd);
	else if (ft_strcmp(lex->cmd->command, "pwd") == 0)
		ft_pwd(lex->env);
	else if (ft_strcmp(lex->cmd->command, "env") == 0)
		print_list_env(lex->env, lex->cmd);
	else if (ft_strcmp(lex->cmd->command, "export") == 0
		&& lex->cmd->argument[1] != NULL)
		ft_export(lex->env, lex->cmd);
	else if (ft_strcmp(lex->cmd->command, "export") == 0)
		lonely_export(lex->env);
	else if (ft_strcmp(lex->cmd->command, "unset") == 0)
		ft_unset(lex->env, lex->cmd);
	else if (ft_strcmp(lex->cmd->command, "cd") == 0)
		ft_cd(lex->cmd, lex->env);
	else if (ft_strcmp(lex->cmd->command, "exit") == 0)
		ft_exit(lex, lex->cmd);
	else
		return (1);
	return (0);
}

size_t	exec_child(t_cmd *cmd_lst, t_exec *exec)
{
	int		ret;

	ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
	if (ret < 0)
		return (exit_stat(errno));
	return (0);
}

void	exec_sys(t_lex *lex)
{
	if (!lex->cmd)
		return ;
	lex->exec = (t_exec *)malloc(sizeof(t_exec));
	ft_exec_init(lex->exec);
	lex->exec->fd = (int **)malloc(sizeof(int *) * get_cmd_len(lex->cmd));
	lex->exec->id = (ssize_t *)malloc(sizeof(ssize_t)
			* (get_cmd_len(lex->cmd) + 1));
	while (lex->exec->i < get_cmd_len(lex->cmd))
	{
		lex->exec->fd[lex->exec->i] = (int *)malloc(sizeof(int) * 2);
		if (!lex->exec || !lex->exec->fd || !lex->exec->id
			|| !lex->exec->fd[lex->exec->i])
		{
			free_env_lst(lex->env);
			free_cmd(&lex->cmd);
			free_exec(&lex->exec);
			exit(EXIT_FAILURE);
		}
		lex->exec->i++;
	}
	fork_arr(lex, lex->exec);
	free_exec(&lex->exec);
}
