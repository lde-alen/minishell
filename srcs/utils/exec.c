/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/13 04:40:41 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	exec_builtin(t_env *lst, t_cmd *cmd_lst)
{
	if (cmd_lst->command[0] == '$')
		ft_expander(lst, cmd_lst->command);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		ft_echo(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		ft_pwd(lst);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		print_list_env(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0
		&& cmd_lst->argument[1] != NULL)
		ft_export(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		lonely_export(lst);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		ft_unset(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "cd") == 0)
		ft_cd(cmd_lst, lst);
	else if (ft_strcmp(cmd_lst->command, "exit") == 0)
		ft_exit(cmd_lst);
	else
		return (1);
	return (0);
}

void	exec_sys(t_lex *lex)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	ft_exec_init(exec);
	exec->fd = (int **)malloc(sizeof(int *) * get_cmd_len(lex->cmd));
	exec->id = (ssize_t *)malloc(sizeof(ssize_t) * (get_cmd_len(lex->cmd) + 1));
	while (exec->i < get_cmd_len(lex->cmd))
	{
		exec->fd[exec->i] = (int *)malloc(sizeof(int) * 2);
		if (!exec || !exec->fd || !exec->id || !exec->fd[exec->i])
		{
			free_cmd(&lex->cmd);
			free_exec(&exec);
			return ;
		}
		exec->i++;
	}
	fork_arr(lex, exec);
	free_exec(&exec);
}

//PROTECT ALL MALLOCS
