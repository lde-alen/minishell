/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/08 18:34:20 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_type(t_cmd *cmd_lst, t_exec **exec)
{
	struct stat	path_stat;

	(*exec)->status = 1;
	if ((stat(cmd_lst->command, &path_stat) == 0) && (S_ISDIR(path_stat.st_mode)))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (cmd_lst->command[get_len(cmd_lst->command) - 1] != '/'
				&& ft_strncmp(cmd_lst->command, "./", 2) != 0)
				(*exec)->status = 0;
			else
			{
				err_msg(cmd_lst, "", "is a directory");
				g_exit = 126;
				return (g_exit);
			}
		}
	}
	// else
	// {
		if (ft_strchr(cmd_lst->command, '/') == 0 || (ft_strchr(cmd_lst->command, '/') == 0 && S_ISDIR(path_stat.st_mode)))
		{
			err_msg(cmd_lst, "", "command not found");
			g_exit = 127;
			return (g_exit);
		}
	// }
	if ((*exec)->path == NULL)
		(*exec)->path = ft_strdup(cmd_lst->command);
	return (0);
}

size_t	main_child2(t_cmd *cmd_lst, t_exec *exec)
{
	int		ret;
	size_t	err;

	err = check_type(cmd_lst, &exec);
	if (err != 0)
		exit(err);
	ret = 0;
	ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
	if (ret < 0)
		perror("Minishell");
	exit(ret);
}

static	size_t	first_child(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	int		ret;
	size_t	err;

	err = check_type(cmd_lst, &exec);
	if (err != 0)
		exit(err);
	ret = 0;
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(exec->fd[exec->i][1]);
	if (check_type(cmd_lst, &exec) == 1)
		exit(ret);
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
	return (ret);
}

static	size_t	last_child(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	int		ret;
	size_t	err;

	err = check_type(cmd_lst, &exec);
	if (err != 0)
		exit(err);
	ret = 0;
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(exec->fd[(exec->i - 1)][0]);
	if (check_type(cmd_lst, &exec) == 1)
		exit(ret);
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
	return (ret);
}

static	size_t	mid_kid(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	int		ret;
	size_t	err;

	err = check_type(cmd_lst, &exec);
	if (err != 0)
		exit(err);
	ret = 0;
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(exec->fd[(exec->i - 1)][0]);
	close(exec->fd[exec->i][1]);
	if (check_type(cmd_lst, &exec) == 1)
		exit(ret);
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
	return (ret);
	// exit(ret);
}

void	free_cmd_lst(t_cmd *cmd_lst)
{
	while (cmd_lst != NULL)
	{
		free_cmd(&cmd_lst);
	}
}

void	check_pos(t_env *lst, t_cmd *cmd_lst, t_exec *exec)
{
	size_t	ret;

	if (exec->i == 0)
		ret = first_child(lst, cmd_lst, exec);
	else if (exec->i + 1 == exec->len)
		ret = last_child(lst, cmd_lst, exec);
	else
		ret = mid_kid(lst, cmd_lst, exec);
	if (exec->env_kid)
		free_env_kid(exec->env_kid);
	ft_printf("PATH IN CHILD: %s\n", exec->path);
	if (exec->path)
		free(exec->path);
	// if (cmd_lst)
	// 	free_cmd(&cmd_lst);
	free_cmd_lst(cmd_lst);
	free_exec(&exec);
	free(exec);
	free_env_lst(lst);
	exit(ret);
}
