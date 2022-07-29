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

// void	second_child(int *fd, t_env *lst, t_cmd *cmd_lst)
// {
// 	close(fd[1]);
// 	if (dup2(fd[0], STDIN_FILENO) < 0)
// 		perror("bash: ");
// 	close(fd[0]);
// 	check_execve(lst, cmd_lst);
// }

// void	pipes(t_env *lst, t_cmd *cmd_lst)
// {
// 	int fd[2];
// 	int id;
// 	int tmp;

// 	tmp = dup(STDOUT_FILENO);
// 	if (pipe(fd) < 0)
// 		perror("bash: ");
// 	id = fork();
// 	if (id < 0)
// 		perror("bash: ");
// 	if (id == 0)
// 	{
// 		ft_printf("boop\n");
// 		close(fd[0]);
// 		if (dup2(fd[1], STDOUT_FILENO) < 0)
// 			perror("bash: ");
// 		close(fd[1]);
// 		check_exec(lst, cmd_lst);
// 	}
// 	second_child(fd, lst, cmd_lst);
// 	close(fd[0]);
// 	close(fd[1]);
// 	dup2(tmp, STDOUT_FILENO);
// 	waitpid(-1, NULL, 0);
// }



void	this()
{
	int	tmp;
	int	tmp2;
	int	id;
	int	file;

	tmp = dup(STDOUT_FILENO);
	tmp2 = dup(STDIN_FILENO);
	id = fork();
	if (id == 0)
	{
		// close(STDOUT_FILENO);
		file = open("test_filie.txt", O_WRONLY | O_APPEND);
		// if (dup(file) < 0)
		// 	perror("dup");
		if (dup2(file, STDOUT_FILENO) < 0)
			perror("dup2");
		ft_printf("Printed\n");
		close(file);
	}
	dup2(tmp, STDOUT_FILENO);
	dup2(tmp2, STDIN_FILENO);
	close(STDOUT_FILENO);
}
