/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/27 09:46:49 by asanthos         ###   ########.fr       */
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
		print_list_env(lst);
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
		exit(0);
	else
		return (1);
	return (0);
}

void	exec_alone(t_cmd *cmd_lst, t_env *lst, t_exec *exec)
{
	if (exec_builtin(lst, cmd_lst) == 0)
	{
		free_cmd(&cmd_lst);
		return ;
	}
	exec->env_kid = lst_to_char(lst);
	exec->id[0] = fork();
	exec->path = check_access(lst, cmd_lst);
	if (exec->id[0] < 0)
		perror("fork");
	else if (exec->id[0] == 0)
		main_child2(cmd_lst, exec);
	free_env_kid(exec->env_kid);
	free(exec->path);
	free_cmd(&cmd_lst);
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	t_exec	*exec;

	ft_memset(&exec, 0, sizeof(t_exec *));
	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->i = 0;
	exec->len = get_cmd_len(cmd_lst);
	exec->fd = (int **)malloc(sizeof(int *) * get_cmd_len(cmd_lst));
	exec->id = (ssize_t *)malloc(sizeof(ssize_t) * (get_cmd_len(cmd_lst) + 1));
	while (exec->i < get_cmd_len(cmd_lst))
	{
		exec->fd[exec->i] = (int *)malloc(sizeof(int) * 2);
		exec->i++;
	}
	if (check_all_path(lst, cmd_lst) == 1)
	{
		free_exec(exec);
		free_cmd(&cmd_lst);
		return ;
	}
	fork_arr(lst, cmd_lst, exec);
	free_exec(exec);
}
