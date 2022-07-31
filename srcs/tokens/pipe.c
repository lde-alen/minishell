/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:25:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 10:25:31 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	second_child(t_env *lst, t_cmd *cmd_lst, int *fd)
{
	char	**params;

	params = (char **)malloc(sizeof(char *) * (get_args_len(cmd_lst) + 1));
	params[0] = cmd_lst->argument[2];
	params[1] = NULL;
	if (dup2(fd[0], STDIN_FILENO) < 0)
		perror("dup2");
	if (execve("/usr/bin/cat", params, lst_to_char(lst)) < 0)
		perror("Execve problem");
	exit(0);
}

static void	first_child(t_env *lst, t_cmd *cmd_lst,int *fd, char *path)
{
	char	**params;

	params = (char **)malloc(sizeof(char *) * (get_args_len(cmd_lst) + 1));
	params[0] = cmd_lst->command;
	params[1] = NULL;
	if (dup2(STDIN_FILENO, STDOUT_FILENO) < 0)
		perror("dup2");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		perror("dup2");
	if (execve(path, params, lst_to_char(lst)) < 0)
		perror("Execve problem");
	exit(0);
}

//need to check path for second command as well
void	exec_pipe(t_env *lst, t_cmd *cmd_lst)
{
	char	*path;
	int		fd[2];
	int		id;
	int		id2;

	path = check_access(lst, cmd_lst);
	if (path != NULL)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		id = fork();
		if (id < 0)
			perror("fork");
		else if (id == 0)
			first_child(lst, cmd_lst, fd, path);
		id2 = fork();
		if (id2 < 0)
			perror("fork");
		else if (id2 == 0)
			second_child(lst, cmd_lst, fd);
	}
	waitpid(-1, NULL, 0);
}
