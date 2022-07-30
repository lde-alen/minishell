/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/30 12:36:29 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	second_child(t_cmd *cmd_lst, int *fd, char *path)
{
	int		id2;
	char	**params;

	(void)path;
	id2 = fork();
	if (id2 < 0)
		perror("fork");
	else if (id2 == 0)
	{
		params = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
		params[0] = cmd_lst->argument[2];
		params[1] = NULL;
		dup2(fd[0], STDIN_FILENO);
		if (execve("/usr/bin/cat", params, NULL) < 0)
			perror("Execve problem");
		exit(0);
	}
}

void	exec_pipe(t_env *lst, t_cmd *cmd_lst)
{
	char	*path;
	char	**params;
	int		fd[2];
	int		id;

	path = check_access(lst, cmd_lst);
	if (path != NULL)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		id = fork();
		if (id < 0)
			perror("fork");
		else if (id == 0)
		{
			params = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
			params[0] = cmd_lst->command;
			params[1] = NULL;
			dup2(STDIN_FILENO, STDOUT_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			if (execve(path, params, NULL) < 0)
				perror("Execve problem");
			exit(0);
		}
		second_child(cmd_lst, fd, path);
		waitpid(-1, NULL, 0);
	}
}
