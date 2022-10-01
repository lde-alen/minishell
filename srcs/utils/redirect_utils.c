/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/30 14:27:06 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	child(t_lex *lex)
{
	int	f_in;
	int	f_out;

	if (lex->cmd->redir->file_in != NULL)
	{
		f_in = open_file(lex, lex->cmd->redir->file_in, lex->cmd->redir->flag_in);
		if (f_in < 0)
		{
			g_exit = 1;
			return (1);
		}
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
		f_out = open_file(lex, lex->cmd->redir->file_out, lex->cmd->redir->flag_out);
		if (f_out < 0)
		{
			g_exit = 1;
			return (1);
		}
		dup2(f_out, STDOUT_FILENO);
		close(f_out);
	}
	return (main_child2(lex));
}

void	redirect(t_lex *lex)
{
	int		id;
	size_t	ret;

	ret = 0;
	if (lex->cmd->argument[0])
	{
		id = fork();
		if (id < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id == 0)
		{
			ret = child(lex);
			free_child(lex);
			exit(ret);
		}
		wait(&g_exit);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
	}
}

int	open_file(t_lex *lex, char *str, int flag)
{
	int		file;
	int		i;

	i = 0;
	while (ft_strcmp(lex->cmd->redir->file[i], str) != 0)
		i++;
	if (str[0] == '/')
	{
		if (access(str, F_OK) != 0)
		{
			if (lex->cmd->redir->flag[i] == R_REDIR || lex->cmd->redir->flag[i] == DR_REDIR)
				err_msg(lex->cmd, str, "Permission denied");
			else if (lex->cmd->redir->flag[i] == L_REDIR)
				err_msg(lex->cmd, str, "No such file or directory");
			g_exit = 1;
			return (-1);
		}
	}
	file = open(str, flag, 0777);
	if (file < 0)
	{
		access(str, F_OK);
		exit_stat(errno);
		return (-1);
	}
	g_exit = 0;
	return (file);
}