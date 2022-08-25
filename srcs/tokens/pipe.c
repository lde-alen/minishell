/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/25 15:47:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_env *lst, t_cmd *cmd_lst, int **fd, ssize_t *id, size_t len, size_t i, size_t flag)
{
	if ((i + 1) != len)
		pipe_arr(fd, i);
	id[i] = fork();
	if (id[i] < 0)
	{
		close_pipes(fd, i, len);
		perror("Fork");
		return ;
	}
	else if (id[i] == 0)
		check_pos(lst, cmd_lst, fd, len, i, flag);
	close_pipes(fd, i, len);
}

void	fork_arr(t_env *lst, t_cmd *cmd_lst, int **fd, ssize_t *id)
{
	char	*path;
	size_t	len;
	size_t	flag;
	size_t	i;

	i = 0;
	flag = 0;
	len = get_cmd_len(cmd_lst);
	path = check_access(lst, cmd_lst);
	if (check_path(cmd_lst, path, &flag) == 1)
		return ;
	if (len > 1)
		loop_lst(lst, &cmd_lst, len, fd, id, flag);
	else
		exec_alone(cmd_lst, lst, id, path);
	free(path);
	i = 0;
	while ((i + 1) <= len)
	{
		wait(NULL);
		i++;
	}
	free_exec(fd, id, len);
}

void	loop_lst(t_env *lst, t_cmd **cmd_lst, size_t len, int **fd, ssize_t *id, size_t flag)
{
	char	*path;
	size_t	i;

	i = 0;
	path = check_access(lst, *cmd_lst);
	if (check_path(*cmd_lst, path, &flag) == 1)
		return ;
	while (*cmd_lst != NULL)
	{
		pipe_exec(lst, *cmd_lst, fd, id, len, i, flag);
		i++;
		free(path);
		free_cmd(cmd_lst);
		if (*cmd_lst != NULL)
		{
			path = check_access(lst, *cmd_lst);
			if (check_path(*cmd_lst, path, &flag) == 1)
				return ;
		}
	}
	if (*cmd_lst && path == NULL)
		ft_putendl_fd("path doesn't exist", 2);
}

void	pipe_arr(int **fd, size_t i)
{
	if (pipe(fd[i]) < 0)
	{
		if (i != 0)
		{
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
		}
		perror("pipe");
	}
}

void	close_pipes(int **fd, size_t i, size_t len)
{
	if (i == 0)
		close(fd[i][1]);
	else if ((i + 1) == len)
		close(fd[i - 1][0]);
	else
	{
		close(fd[i - 1][0]);
		close(fd[i][1]);
	}
}
