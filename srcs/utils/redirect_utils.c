/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/16 12:06:37 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_env *lst, t_cmd *cmd_lst, int status, char *path, char *file_name)
{
	int		file;

	int file2 = open("store.txt", O_RDONLY, 0777);
	file = open(file_name, O_CREAT | O_RDWR, 0777);
	dup2(file2, STDIN_FILENO);
	dup2(file, status);
	close(file);
	close(file2);
	execve(path, cmd_lst->argument, lst_to_char(&lst));
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
void	redirect(t_env *lst, t_cmd *cmd_lst, int flag, int status, size_t i)
{
	int		file;

	//0777 needed for append redirect
	file = open(cmd_lst->redir->file[i], flag, 0777);
	if (file < 0)
	{
		perror("file");
		return ;
	}
	//replace with exec_sys()
	exec(lst, cmd_lst, status, cmd_lst->redir->file[i]);
}

void	open_file(char *str, int flag)
{
	int		file;

	//0777 needed for append redirect
	file = open(str, flag, 0777);
	if (file < 0)
	{
		perror("minishell");
		return ;
	}
}