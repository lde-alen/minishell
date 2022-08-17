/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/17 16:57:29 by asanthos         ###   ########.fr       */
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
	int	j;

	j = 0;
	while (cmd_lst != NULL)
	{
		if (j != i)
			close(fd[j][1]);
		close(fd[j][0]);
		j++;
		cmd_lst = cmd_lst->next;
	}
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd[i][1]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	last_child(t_cmd *cmd_lst, int (*fd)[2], char *path, char **env_kid, int i, int len)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		if (j != (i - 1))
			close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	if (dup2(fd[(i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(fd[(i - 1)][0]);
	ft_printf("%s\n", path);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
} 


void	mid_kid(t_cmd *cmd_lst, int (*fd)[2], char *path, char **env_kid, int i, int len)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		if (j != i)
			close(fd[j][1]);
		if (j != (i - 1))
			close(fd[j][0]);
		i++;
	}
	int b = 0;
	ft_printf("Mid child\n");
	while (cmd_lst->argument[b])
	{
		ft_printf("%s\n", cmd_lst->argument[b]);
		b++;
	}
	ft_printf("%s\n", cmd_lst->argument[i]);
	if (dup2(fd[(i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(fd[(i - 1)][0]);
	close(fd[i][1]);
	ft_printf("%s\n", path);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

void	pipe_arr(t_cmd *cmd_lst, int (*fd)[2])
{
	int		i;

	i = 0;
	while (cmd_lst != NULL)
	{
		if (pipe(fd[i]) < 0)
		{
			while (i >= 0)
			{
				close(fd[i][0]);
				close(fd[i][1]);
				i--;
			}
			perror("pipe");
		}
		i++;
		cmd_lst = cmd_lst->next;
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
		last_child(cmd_lst, fd, path, env_kid, i, len);
	else
		mid_kid(cmd_lst, fd, path, env_kid, i, len);
}

void	close_all_pipes(t_cmd *cmd_lst, int (*fd)[2])
{
	int	i;

	i = 0;
	while (cmd_lst != NULL)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
		cmd_lst = cmd_lst->next;
	}
	ft_printf("value of i: %d\n", i);
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
			pipe_arr(cmd_lst, fd);
			id[i] = fork();
			if (id[i] < 0)
			{
				close_all_pipes(cmd_lst, fd);
				perror("Fork");
				return ;
			}
			else if (id[i] == 0)
				check_pos(lst, cmd_lst, fd, len, i);
			close_all_pipes(cmd_lst, fd);
			i++;
			tmp = cmd_lst;
			cmd_lst = cmd_lst->next;
			free(tmp);
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
