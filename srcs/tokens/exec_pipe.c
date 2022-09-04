/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/04 17:18:28 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_type(t_cmd *cmd_lst, t_exec **exec)
{
	struct stat	path_stat;

	if (stat(cmd_lst->command, &path_stat) > 0 && S_ISDIR(path_stat.st_mode))
	{
		if (cmd_lst->command[get_len(cmd_lst->command) - 1] != '/'
			&& ft_strncmp(cmd_lst->command, "./", 2) != 0)
			(*exec)->path = NULL;
		else
		{
			err_msg(cmd_lst, "", "Is a directory");
			g_exit = 126;
			return (1);
		}
	}
	if ((*exec)->path == NULL)
	{
		if (ft_strchr(cmd_lst->command, '/') == 0)
		{
			err_msg(cmd_lst, "", "command not found");
			g_exit = 127;
			return (1);
		}
		(*exec)->path = ft_strdup(cmd_lst->command);
	}
	return (0);
}

void	main_child2(t_cmd *cmd_lst, t_exec *exec)
{
	int	ret;

	if (check_type(cmd_lst, &exec) == 1)
		return ;
	ret = 0;
	ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
	if (ret < 0)
		perror("Minishell");
	exit(ret);
}

static	void	first_child(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	int	ret;

	ret = 0;
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(exec->fd[exec->i][1]);
	if (check_type(cmd_lst, &exec) == 1)
		return ;
	if (exec->flag == 1)
	{
		exec->flag = 2;
		exec_builtin(lst, cmd_lst);
		ret = 0;
	}
	else
	{
		ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
		if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
			perror("Minishell");
	}
	exit(ret);
}

static	void	last_child(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	int	ret;

	ret = 0;
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(exec->fd[(exec->i - 1)][0]);
	if (check_type(cmd_lst, &exec) == 1)
		return ;
	if (exec->flag == 1)
	{
		exec->flag = 2;
		exec_builtin(lst, cmd_lst);
		ret = 0;
	}
	else
	{
		ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
		if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
			perror("Minishell");
	}
	exit(ret);
}

static	void	mid_kid(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	int	ret;

	ret = 0;
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(exec->fd[(exec->i - 1)][0]);
	close(exec->fd[exec->i][1]);
	// if (check_type(cmd_lst, &exec) == 1)
	// 	return ;
	if (exec->flag == 1)
	{
		exec->flag = 2;
		exec_builtin(lst, cmd_lst);
		ret = 0;
	}
	else
	{
		ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
		if (execve(exec->path, cmd_lst->argument, exec->env_kid) < 0)
			perror("Minishell");
	}
	exit(ret);
}

void	check_pos(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	exec->env_kid = lst_to_char(&lst);
	exec->path = check_access(lst, cmd_lst);
	if (exec->i == 0)
		first_child(lst, cmd_lst, exec);
	else if (exec->i + 1 == exec->len)
		last_child(lst, cmd_lst, exec);
	else
		mid_kid(lst, cmd_lst, exec);
	free(exec->path);
	free_cmd(&cmd_lst);
	free_env_kid(exec->env_kid);
}
