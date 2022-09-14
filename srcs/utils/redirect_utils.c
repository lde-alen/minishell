/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/13 15:51:21 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_env *lst, t_cmd *cmd_lst, int status, char *path, char *file_name)
{
	char	**params;
	int		file;

	file = open(file_name, O_CREAT | O_RDWR, 0777);
	params = (char **)malloc(sizeof(char *) * (get_args_len(cmd_lst) + 1));
	params[0] = cmd_lst->command;
	params[1] = NULL;
	dup2(file, status);
	close(file);
	execve(path, params, lst_to_char(&lst));
	ft_printf("failed\n");
	exit(0);
}

void	exec(t_env *lst, t_cmd *cmd_lst, int status, char *file)
{
	char	*path;
	int		id;

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

//basis for all redirections
void	redirect(t_env *lst, t_cmd *cmd_lst, int flag, int status)
{
	int		file;

	//0777 needed for append redirect
	file = open(cmd_lst->argument[2], flag, 0777);
	if (file < 0)
	{
		perror("file");
		return ;
	}
	//replace with exec_sys()
	exec(lst, cmd_lst, status, cmd_lst->argument[2]);
}

void	open_file(t_cmd *cmd_lst, int flag)
{
	int		file;

	//0777 needed for append redirect
	file = open(cmd_lst->argument[2], flag, 0777);
	if (file < 0)
	{
		perror("file");
		return ;
	}
}