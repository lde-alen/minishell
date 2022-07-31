/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 10:07:56 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child(t_env *lst, t_cmd *cmd_lst, int status, char *path, int file)
{
	char	**params;

	params = (char **)malloc(sizeof(char *) * (get_args_len(cmd_lst) + 1));
	params[0] = cmd_lst->command;
	params[1] = NULL;
	dup2(file, status);
	close(file);
	execve(path, params, lst_to_char(lst));
	exit(0);
}

void	redirect(t_env *lst, t_cmd *cmd_lst, int flag, int status)
{
	int		file;
	int		id;
	char	*path;

	//0777 needed for append redirect
	file = open(cmd_lst->argument[2], flag, 0777);
	if (file < 0)
	{
		perror("file");
		return ;
	}
	path = check_access(lst, cmd_lst);
	if (path != NULL)
	{
		id = fork();
		if (id < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id == 0)
			child(lst, cmd_lst, status, path, file);
		waitpid(-1, NULL, 0);
	}
	free(path);
}
