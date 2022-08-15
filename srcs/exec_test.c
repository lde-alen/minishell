/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/14 22:16:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int i, int len, int **fd)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		if (j != i)
			close(fd[j][1]);
		if (j != i - 1)
			close(fd[j][0]);
		i++;
	}
}

void	main_child2(t_cmd *cmd_lst, char *path, char **env_kid)
{
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	first_child(t_cmd *cmd_lst,int **fd, char *path, char **env_kid, int i, int len)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		if (j != i)
			close(fd[j][1]);
		i++;
	}
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd[i][1]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	second_child(t_cmd *cmd_lst, int **fd, char *path, char **env_kid, int i, int len)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		if (j != i - 1)
			close(fd[j][0]);
		i++;
	}
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0)
		perror("dup2");
	close(fd[i - 1][0]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

void	mid_kid(t_cmd *cmd_lst,int **fd, char *path, char **env_kid, int i, int len)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		if (j != i)
			close(fd[j][1]);
		if (j != i - 1)
			close(fd[j][0]);
		i++;
	}
	// int i = 0;
	// ft_printf("Mid child\n");
	// while (cmd_lst->argument[i])
	// {
	// 	ft_printf("%s\n", cmd_lst->argument[i]);
	// 	i++;
	// }
	// ft_printf("%s\n", cmd_lst->argument[i]);
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd[i - 1][0]);
	close(fd[i][1]);
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

void	pipe_arr(t_cmd *cmd_lst, int ***fd)
{
	int		i;

	i = 0;
	while (i <= get_cmd_len(cmd_lst))
	{
		if (pipe(*fd[i]) < 0)
		{
			while (i >= 0)
			{
				close(*fd[i][0]);
				close(*fd[i][1]);
				i--;
			}
			perror("pipe");
		}
		i++;
	}
}

void	check_pos(t_env *lst, t_cmd *cmd_lst, int **fd, int len, int i)
{
	char	**env_kid;
	char	*path;

	env_kid = lst_to_char(lst);
	path = check_access(lst, cmd_lst);
	if (i == 0)
	{
		ft_printf("HERE1\n");
		first_child(cmd_lst, &(*fd), path, env_kid, i, len);
	}
	else if (i + 1 == len)
	{
		ft_printf("HERE2\n");
		second_child(cmd_lst, &(*fd), path, env_kid, i, len);
	}
	else
	{
		ft_printf("HERE3\n");
		mid_kid(cmd_lst, &(*fd), path, env_kid, i, len);
	}
}

void	fork_arr(t_env *lst, t_cmd *cmd_lst, int **fd, int *id)
{
	int		i;
	int		len;
	t_cmd	*tmp;

	i = 0;
	len = get_cmd_len(cmd_lst);
	while (cmd_lst != NULL)
	{
		id[i] = fork();
		if (id[i] < 0)
		{
			i = 0;
			while (i <= len)
			{
				close(fd[i][0]);
				close(fd[i][1]);
				i++;
			}
		}
		else if (id[i] == 0)
		{
		//	close_pipes(i, len, fd);
			check_pos(lst, cmd_lst, &(*fd), len, i);
		}
		i++;
		tmp = cmd_lst;
		cmd_lst = cmd_lst->next;
		free(tmp);
	}
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
	pipe_arr(cmd_lst, &fd);
	fork_arr(lst, cmd_lst, &(*fd), *(&id));
}
