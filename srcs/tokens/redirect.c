/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 03:32:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_in(t_env *lst, t_cmd *cmd_lst)
{
	int		file;
	int		id;
	char	*path;
	char	**params;

	file = open(cmd_lst->argument[2], O_RDONLY);
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
			params = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
			params[0] = cmd_lst->command;
			params[1] = NULL;
			dup2(file, STDIN_FILENO);
			close(file);
			execve(path, params, NULL);
			exit(0);
		}
		waitpid(-1, NULL, 0);
	}
}

//test cat > file_name
void	redirect_out(t_env *lst, t_cmd *cmd_lst)
{
	int		file;
	int		id;
	char	*path;
	char	**params;

	file = open(cmd_lst->argument[2], O_TRUNC | O_CREAT | O_WRONLY);
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
			params = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
			params[0] = cmd_lst->command;
			params[1] = NULL;
			dup2(file, STDOUT_FILENO);
			close(file);
			if (execve(path, params, NULL) < 0)
				perror("Execve");
			exit(0);
		}
		waitpid(-1, NULL, 0);
	}
}

void	append_out(t_env *lst, t_cmd *cmd_lst)
{
	int		file;
	int		id;
	char	*path;
	char	**params;

	file = open(cmd_lst->argument[2], O_APPEND | O_WRONLY | O_CREAT, 0777);
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
			params = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
			params[0] = cmd_lst->command;
			params[1] = NULL;
			dup2(file, STDOUT_FILENO);
			close(file);
			if (execve(path, params, NULL) < 0)
				perror("Execve");
			exit(0);
		}
		waitpid(-1, NULL, 0);
	}
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
			execve(path, params, NULL);
			exit(0);
		}
	}
	waitpid(-1, NULL, 0);
	unlink("store.txt");
}
