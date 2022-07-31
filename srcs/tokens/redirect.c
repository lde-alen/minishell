/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 07:57:11 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect(t_env *lst, t_cmd *cmd_lst, int flag, int status)
{
	int		file;
	int		id;
	char	*path;
	char	**params;

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
		{
			params = (char **)malloc(sizeof(char *) * (get_args_len(cmd_lst) + 1));
			params[0] = cmd_lst->command;
			params[1] = NULL;
			dup2(file, status);
			close(file);
			execve(path, params, lst_to_char(lst));
			exit(0);
		}
		waitpid(-1, NULL, 0);
	}
	free(path);
}

void	redirect_in(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_RDONLY;
	status = STDIN_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

//test cat > file_name
void	redirect_out(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_TRUNC | O_CREAT | O_WRONLY;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

void	append_out(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_APPEND | O_WRONLY | O_CREAT;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

void	here_doc(t_env *lst, t_cmd *cmd_lst)
{
	int		file;
	int		id2;
	char	*path;
	char	*str;
	char	**params;

	path = check_access(lst, cmd_lst);
	file = open("store.txt", O_TRUNC | O_CREAT | O_RDWR);
	str = "";
	while (strcmp(str, cmd_lst->argument[2]) != 0)
	{
		str = readline("> ");
		ft_putendl_fd(str, file);
	}
	if (path != NULL)
	{
		id2 = fork();
		if (id2 < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id2 == 0)
		{
			params = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
			params[0] = cmd_lst->command;
			params[1] = NULL;
			dup2(file, STDIN_FILENO);
			close(file);
			execve(path, params, lst_to_char(lst));
			exit(0);
		}
	}
	waitpid(-1, NULL, 0);
	free(path);
	unlink("store.txt");
}
