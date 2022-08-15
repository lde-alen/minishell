/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:49:15 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/14 13:25:09 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_kid(char **env_kid)
{
	int	i;

	i = 0;
	while (env_kid[i])
	{
		free(env_kid[i]);
		i++;
	}
	free(env_kid[i]);
	free(env_kid);
}

void	main_child2(t_cmd *cmd_lst, char *path, char **env_kid)
{
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	first_child(t_cmd *cmd_lst,int *fd, char *path, char **env_kid)
{
	
	int i = 0;
	ft_printf("First child\n");
	while (cmd_lst->argument[i])
	{
		ft_printf("%s\n", cmd_lst->argument[i]);
		i++;
	}
	ft_printf("%s\n", cmd_lst->argument[i]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		perror("dup2");
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

static void	second_child(t_cmd *cmd_lst, int *fd, char *path, char **env_kid)
{
	int i = 0;
	ft_printf("Second child\n");
	while (cmd_lst->argument[i])
	{
		ft_printf("%s\n", cmd_lst->argument[i]);
		i++;
	}
	ft_printf("%s\n", cmd_lst->argument[i]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		perror("dup2");
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

void	mid_kid(t_cmd *cmd_lst,int *fd, char *path, char **env_kid)
{
	int i = 0;
	ft_printf("Mid child\n");
	while (cmd_lst->argument[i])
	{
		ft_printf("%s\n", cmd_lst->argument[i]);
		i++;
	}
	ft_printf("%s\n", cmd_lst->argument[i]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		perror("dup2");
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	exit(0);
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	t_cmd	*tmp;
	char	**env_kid;
	char	*path;
	int		fd[2];
	int		id;
	int		i;
	int		len;

	i = 0;
	env_kid = lst_to_char(lst);
	path = check_access(lst, cmd_lst);
	if (path != NULL)
	{
		len = get_cmd_len(cmd_lst);
		if (len > 1)
		{
			if (pipe(fd) < 0)
				perror("pipe");
			while (i < get_cmd_len(cmd_lst))
			{
				path = check_access(lst, cmd_lst);
				if (!path)
				{
					perror("PATH");
					return ;
				}
				id = fork();
				if (id < 0)
					ft_putendl_fd("Fork failed", 2);
				else if (id == 0)
				{
					if (i == 0)
					{
						ft_printf("HERE1\n");
						first_child(cmd_lst, fd, path, env_kid);
					}
					else if (i + 1 == len)
					{
						ft_printf("HERE2\n");
						second_child(cmd_lst, fd, path, env_kid);
					}
					else
					{
						ft_printf("HERE3\n");
						mid_kid(cmd_lst, fd, path, env_kid);
					}
				}
				if (cmd_lst->next != NULL)
				{
					tmp = cmd_lst;
					cmd_lst = cmd_lst->next;
					free(tmp);
				}
				else
				{
					free(cmd_lst);
					break;
				}
				i++;
			}
			waitpid(-1, NULL, 0);
		}
		else
		{
			id = fork();
			if (id < 0)
				ft_putendl_fd("Fork failed", 2);
			else if (id == 0)
			{
				ft_printf("HERE4\n");
				main_child2(cmd_lst, path, env_kid);
			}
			waitpid(-1, NULL, 0);
			free(cmd_lst);
		}
	}
	else
		perror("path");
	free(path);
	free_env_kid(env_kid);
}



// void	exec_sys(t_env *lst, t_cmd *cmd_lst)
// {
// 	char	**env_kid;
// 	char	*path;
// 	int		id;

// 	id = fork();
// 	env_kid = lst_to_char(lst);
// 	path = check_access(lst, cmd_lst);
// 	if (path != NULL)
// 	{
// 		if (id < 0)
// 			ft_putendl_fd("Fork failed", 2);
// 		else if (id == 0)
// 			main_child2(lst, cmd_lst, path, env_kid);
// 		waitpid(-1, NULL, 0);
// 	}
// 	free(path);
// 	free_env_kid(env_kid);
// }
