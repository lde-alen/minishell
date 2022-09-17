/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/17 14:20:45 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_env *lst, t_cmd *cmd_lst, int status, char *path, char *file_name, int flag)
{
	int		file;
	int		file2;

	if (file_name)
	{
		file = open_file(file_name, flag);
		dup2(file, status);
		close(file);
	}
	file2 = open_file("store.txt", O_RDONLY);
	dup2(file2, STDIN_FILENO);
	close(file2);
	execve(path, cmd_lst->argument, lst_to_char(&lst));
	ft_printf("failed\n");
	exit(0);
}

void	exec_tok(t_env *lst, t_cmd *cmd_lst, int status, char *file, int flag)
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
			child(lst, cmd_lst, status, path, file, flag);
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
	exec_tok(lst, cmd_lst, status, cmd_lst->redir->file[i], flag);
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