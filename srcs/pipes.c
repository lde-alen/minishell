/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 06:17:48 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/25 14:49:14 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipes(t_env *lst, t_cmd *cmd_lst)
{
	int fd[2];
	int id;
	if (pipe(fd) < 0)
		perror("bash: ");
	id = fork();
	if (id < 0)
		perror("bash: ");
	if (id == 0)
	{
		ft_printf("boop\n");
		if (dup2(fd[0], STDIN_FILENO) < 0)
			perror("bash: ");
		if (dup2(fd[1], STDIN_FILENO) < 0)
			perror("bash: ");
		close(fd[0]);
		close(fd[1]);
		check_exec(lst, cmd_lst);
	}
	waitpid(-1, NULL, 0);
}
