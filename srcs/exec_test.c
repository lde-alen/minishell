/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/18 16:08:36 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_child2(t_cmd *cmd_lst, char *path, char **env_kid)
{
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	first_child(t_cmd *cmd_lst, int (*fd)[2], char *path, char **env_kid, int i)
{
	close(fd[i][0]);
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd[i][1]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	last_child(t_cmd *cmd_lst, int (*fd)[2], char *path, char **env_kid, int i)
{
	if (dup2(fd[(i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(fd[(i - 1)][0]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
} 


void	mid_kid(t_cmd *cmd_lst, int (*fd)[2], char *path, char **env_kid, int i)
{
	close(fd[i][0]);
	if (dup2(fd[(i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(fd[(i - 1)][0]);
	close(fd[i][1]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

void	pipe_arr(int (*fd)[2], int i)
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

void	check_pos(t_env *lst, t_cmd *cmd_lst, int (*fd)[2], int len, int i)
{
	char	**env_kid;
	char	*path;

	env_kid = lst_to_char(lst);
	path = check_access(lst, cmd_lst);
	if (i == 0)
		first_child(cmd_lst, fd, path, env_kid, i);
	else if (i + 1 == len)
		last_child(cmd_lst, fd, path, env_kid, i);
	else
		mid_kid(cmd_lst, fd, path, env_kid, i);
}

void	close_pipes(int (*fd)[2], int i, int len)
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

void	exec_alone(t_cmd *cmd_lst, t_env *lst, int *id, char *path)
{
	char	**env_kid;

	env_kid = lst_to_char(lst);
	id[0] = fork();
	if (id[0] < 0)
		perror("fork");
	else if (id[0] == 0)
		main_child2(cmd_lst, path, env_kid);
	free(path);
}

void	fork_arr(t_env *lst, t_cmd *cmd_lst, int (*fd)[2], int *id)
{
	t_cmd	*tmp;
	char	*path;
	int		len;
	int		i;

	i = 0;
	len = get_cmd_len(cmd_lst);
	path = check_access(lst, cmd_lst);
	if (path == NULL)
	{
		perror("path error");
		return ;
	}
	if (len > 1)
	{
		while (cmd_lst != NULL)
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
				check_pos(lst, cmd_lst, fd, len, i);
			close_pipes(fd, i, len);
			i++;
			tmp = cmd_lst;
			cmd_lst = cmd_lst->next;
			free(tmp);
			free(path);
			if (cmd_lst != NULL)
			{
				path = check_access(lst, cmd_lst);
				if (path == NULL)
				{
					perror("path error");
					return ;
				}
			}
		}
		if (cmd_lst && path == NULL)
			ft_putendl_fd("path doesn't exist", 2);
	}
	else
		exec_alone(cmd_lst, lst, id, path);
	waitpid(-1, NULL, 0);
}

int	check_all_path(t_env *lst, t_cmd *cmd_lst)
{
	while (cmd_lst != NULL)
	{
		if (check_access(lst, cmd_lst) == NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_lst->argument[0], 2);
			ft_putendl_fd(": command not found\n", 2);
			return (1);
		}
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	int		fd[get_cmd_len(cmd_lst)][2];
	int		id[get_cmd_len(cmd_lst) + 1];

	if (check_all_path(lst, cmd_lst) == 1)
		return ;
	fork_arr(lst, cmd_lst, fd, id);
}
