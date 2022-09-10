/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/10 17:31:47 by asanthos         ###   ########.fr       */
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

void	exec_alone(t_cmd *cmd_lst, t_env *lst, t_exec *exec)
{
	size_t	ret;

	if (exec_builtin(lst, cmd_lst) == 0)
	{
		exec->flag = 2;
		return ;
	}
	exec->env_kid = lst_to_char(&lst);
	exec->id[0] = fork();
	if (exec->id[0] < 0)
		perror("fork");
	else if (exec->id[0] == 0)
	{
		ret = main_child2(cmd_lst, exec);
		free_env_kid(exec->env_kid);
		// free_exec(&exec);
		// free(exec);
		free_env_lst(lst);
		free_cmd(&cmd_lst);
		ft_printf("value of g_ex = %d\n", g_exit);
		ft_printf("value of ret = %d\n", ret);
		exit (ret);
	}
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	t_exec	*exec;

	ft_memset(&exec, 0, sizeof(t_exec *));
	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->i = 0;
	exec->fd = (int **)malloc(sizeof(int *) * get_cmd_len(cmd_lst));
	exec->id = (ssize_t *)malloc(sizeof(ssize_t) * (get_cmd_len(cmd_lst) + 1));
	while (exec->i < get_cmd_len(cmd_lst))
	{
		exec->fd[exec->i] = (int *)malloc(sizeof(int) * 2);
		if (!exec || !exec->fd || !exec->id || !exec->fd[exec->i])
		{
			free_cmd(&cmd_lst);
			free_exec(&exec);
			return ;
		}
		exec->i++;
	}
	// if (check_all_path(lst, cmd_lst) == 1)
	// 	return ;
	fork_arr(lst, cmd_lst, exec);
	free_exec(&exec);
	free(exec);
}

//PROTECT ALL MALLOCS
