/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/17 19:28:36 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_env *lst, t_cmd *cmd_lst, int status, char *file_name, int flag, t_exec *exec)
{
	int		file;
	int		file2;

	(void)lst;
	if (file_name)
	{
		file = open_file(file_name, flag);
		dup2(file, status);
		close(file);
	}
	file2 = open_file("store.txt", O_RDONLY);
	dup2(file2, STDIN_FILENO);
	close(file2);
	main_child2(lst, cmd_lst, exec);
}

void	redirect(t_env *lst, t_cmd *cmd_lst, int status, char *file, int flag, t_exec *exec)
{
	int		id;

	exec->path = check_access(lst, cmd_lst);
	if (exec->path != NULL)
	{
		id = fork();
		if (id < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id == 0)
			child(lst, cmd_lst, status, file, flag, exec);
		waitpid(-1, NULL, 0);
	}
	free(exec->path);
}

int	open_file(char *str, int flag)
{
	int		file;

	//0777 needed for append redirect
	file = open(str, flag, 0777);
	if (file < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (file);
}