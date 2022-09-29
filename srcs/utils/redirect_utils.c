/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/29 14:26:26 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	child(t_lex *lex, t_exec *exec)
{
	int	f_in;
	int	f_out;

	if (lex->cmd->redir->file_in != NULL)
	{
		f_in = open_file(lex->cmd->redir->file_in, lex->cmd->redir->flag_in);
		if (f_in < 0)
			return (-1);
		dup2(f_in, STDIN_FILENO);
		close(f_in);
	}
	else if (lex->cmd->redir->flag_in == -1)
	{
		dup2(lex->cmd->redir->fd[0], STDIN_FILENO);
		close(lex->cmd->redir->fd[0]);
	}
	if (lex->cmd->redir->file_out != NULL)
	{
		f_out = open_file(lex->cmd->redir->file_out, lex->cmd->redir->flag_out);
		if (f_out < 0)
			return (-1);
		dup2(f_out, STDOUT_FILENO);
		close(f_out);
	}
	return (main_child2(lex->env, lex->cmd, exec));
}

void	redirect(t_lex *lex, t_exec *exec)
{
	int		id;
	size_t	ret;

	ret = 0;
	if (lex->cmd->argument[0])
	{
		if (exec->path != NULL)
		{
			id = fork();
			if (id < 0)
				ft_putendl_fd("Fork failed", 2);
			else if (id == 0)
			{
				ret = child(lex, exec);
				free_child(lex);
				exit(ret);
			}
			wait(NULL);
		}
	}
}

int	open_file(char *str, int flag)
{
	int		file;

	file = open(str, flag, 0777);
	if (file < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (file);
}