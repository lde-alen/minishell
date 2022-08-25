/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/25 14:41:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_child2(t_cmd *cmd_lst, char *path, char **env_kid)
{
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static	void	first_child(t_env *lst, t_cmd *cmd_lst, int **fd, char *path, char **env_kid, size_t i, size_t flag)
{
	close(fd[i][0]);
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd[i][1]);
	if (flag == 1)
		exec_builtin(lst, cmd_lst);
	else
	{
		if (execve(path, cmd_lst->argument, env_kid) < 0)
			perror("Execve problem");
	}
	exit(0);
}

static	void	last_child(t_env *lst, t_cmd *cmd_lst, int **fd, char *path, char **env_kid, size_t i, size_t flag)
{
	if (dup2(fd[(i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(fd[(i - 1)][0]);
	if (flag == 1)
		exec_builtin(lst, cmd_lst);
	else
	{
		if (execve(path, cmd_lst->argument, env_kid) < 0)
			perror("Execve problem");
	}
	exit(0);
}

static	void	mid_kid(t_env *lst, t_cmd *cmd_lst, int **fd, char *path, char **env_kid, size_t i, size_t flag)
{
	close(fd[i][0]);
	if (dup2(fd[(i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(fd[(i - 1)][0]);
	close(fd[i][1]);
	if (flag == 1)
		exec_builtin(lst, cmd_lst);
	else
	{
		if (execve(path, cmd_lst->argument, env_kid) < 0)
			perror("Execve problem");
	}
	exit(0);
}

void	check_pos(t_env *lst, t_cmd *cmd_lst, int **fd, size_t len, size_t i, size_t flag)
{
	char	**env_kid;
	char	*path;

	env_kid = lst_to_char(lst);
	path = check_access(lst, cmd_lst);
	if (i == 0)
		first_child(lst, cmd_lst, fd, path, env_kid, i, flag);
	else if (i + 1 == len)
		last_child(lst, cmd_lst, fd, path, env_kid, i, flag);
	else
		mid_kid(lst, cmd_lst, fd, path, env_kid, i, flag);
	free(path);
	free_cmd(&cmd_lst);
	free_env_kid(env_kid);
}
