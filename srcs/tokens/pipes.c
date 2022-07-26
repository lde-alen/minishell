/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:06:33 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/26 11:49:37 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	second_child(int *fd, t_env *lst, t_cmd *cmd_lst)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		perror("bash: ");
	close(fd[0]);
	check_execve(lst, cmd_lst);
}

void	pipes(t_env *lst, t_cmd *cmd_lst)
{
	int fd[2];
	int id;
	int tmp;

	tmp = dup(STDOUT_FILENO);
	if (pipe(fd) < 0)
		perror("bash: ");
	id = fork();
	if (id < 0)
		perror("bash: ");
	if (id == 0)
	{
		ft_printf("boop\n");
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror("bash: ");
		close(fd[1]);
		check_exec(lst, cmd_lst);
	}
	second_child(fd, lst, cmd_lst);
	close(fd[0]);
	close(fd[1]);
	dup2(tmp, STDOUT_FILENO);
	waitpid(-1, NULL, 0);
}
