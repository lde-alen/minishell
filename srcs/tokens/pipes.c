/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:06:33 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/29 05:32:38 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	main_child2(t_env *lst, t_cmd *cmd_lst, char *path)
{
	char	**av;

	(void)lst;
	av = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
	av[0] = cmd_lst->command;
	av[1] = NULL;
	if (execve(path, av, NULL) < 0)
		perror("Execve problem");
}

void	check_execve(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_path;
	char	*post_join;
	char	*path;
	char	*str;
	int		id;
	int		i;

	i = 0;
	env_path = get_path(lst);
	while (env_path[i])
	{
		post_join = ft_strjoin("/", cmd_lst->command);
		str = ft_strjoin(env_path[i], post_join);
		if (access(str, F_OK) == 0)
		{
			path = ft_strdup(str);
			id = fork();
			if (id < 0)
				ft_putendl_fd("Fork failed", 2);
			else if (id == 0)
				main_child2(lst, cmd_lst, path);
			waitpid(-1, NULL, 0);
			free(str);
			free(post_join);
		}
		i++;
	}
}

void	main_child3(t_env *lst, t_cmd *cmd_lst, char *path)
{
	char	**av;

	(void)lst;
	av = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
	av[0] = cmd_lst->argument[2];
	av[1] = NULL;
	if (execve(path, av, NULL) < 0)
		perror("Execve problem");
}

void	check_execve2(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_path;
	char	*post_join;
	char	*path;
	char	*str;
	int		id;
	int		i;

	i = 0;
	env_path = get_path(lst);
	while (env_path[i])
	{
		post_join = ft_strjoin("/", cmd_lst->argument[2]);
		str = ft_strjoin(env_path[i], post_join);
		if (access(str, F_OK) == 0)
		{
			path = ft_strdup(str);
			id = fork();
			if (id < 0)
				ft_putendl_fd("Fork failed", 2);
			else if (id == 0)
				main_child3(lst, cmd_lst, path);
			waitpid(-1, NULL, 0);
			free(str);
			free(post_join);
		}
		i++;
	}
}

void	second_child(t_env *lst, t_cmd *cmd_lst, int *fd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		close(fd[1]);
		if (dup2(STDOUT_FILENO, fd[0]) < 0)
			perror("dup2");
		check_execve2(lst, cmd_lst);
		close(fd[1]);
		exit(0);
	}
}

void	pipes(t_env *lst, t_cmd *cmd_lst)
{
	int	id;
	int	fd[2];

	id = fork();
	pipe(fd);
	if (id == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror("dup2");
		check_execve(lst, cmd_lst);
		close(fd[1]);
		exit(0);
	}
	second_child(lst, cmd_lst, fd);
	waitpid(-1, NULL, 0);
	dup2(STDOUT_FILENO, fd[0]);
}
