/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/19 17:16:28 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_lex *lex, t_exec *exec)
{
	int	f_in;
	int	f_out;

	if (lex->cmd->redir->file_in != NULL)
	{
		f_in = open_file(lex->cmd->redir->file_in, lex->cmd->redir->flag_in);
		dup2(f_in, STDIN_FILENO);
		close(f_in);
	}
	if (lex->cmd->redir->file_out != NULL)
	{
		f_out = open_file(lex->cmd->redir->file_out, lex->cmd->redir->flag_out);
		dup2(f_out, STDOUT_FILENO);
		close(f_out);
	}





	// int		file;
	// // int		file2;

	// (void)lst;
	// (void)lex;
	// if (file_name)
	// {
	// 	file = open_file(file_name, flag);
	// 	dup2(file, status);
	// 	close(file);
	// }
	// file2 = open_file("store.txt", O_RDONLY);
	// dup2(file2, STDIN_FILENO);
	// close(file2);
	main_child2(lex->env, lex->cmd, exec);
}

void	redirect(t_lex *lex, t_exec *exec)
{
	int		id;

	exec->path = check_access(lex->env, lex->cmd);
	if (exec->path != NULL)
	{
		id = fork();
		if (id < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id == 0)
		{
			//CHECK REDIR TYPE
			child(lex, exec);
		}
		waitpid(-1, NULL, 0);
	}
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