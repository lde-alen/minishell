/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/17 16:10:43 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	dup_stdin(t_lex *lex, ssize_t *f_in)
{
	if (lex->cmd->redir->file_in != NULL)
	{
		*f_in = open_file(lex, lex->cmd->redir->file_in,
				lex->cmd->redir->flag_in);
		if (dup2(*f_in, STDIN_FILENO) < 0 || *f_in < 0)
		{
			g_exit = 1;
			return (1);
		}
		close(*f_in);
	}
	else if (lex->cmd->redir->flag_in == -1)
	{
		if (dup2(lex->cmd->redir->fd[0], STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close(lex->cmd->redir->fd[0]);
	}
	return (0);
}

size_t	dup_stdout(t_lex *lex, ssize_t *f_out)
{
	if (lex->cmd->redir->file_out != NULL)
	{
		*f_out = open_file(lex, lex->cmd->redir->file_out,
				lex->cmd->redir->flag_out);
		if (dup2(*f_out, STDOUT_FILENO) < 0 || *f_out < 0)
		{
			g_exit = 1;
			return (1);
		}
		close(*f_out);
	}
	return (0);
}

static size_t	child(t_lex *lex)
{
	ssize_t	f_in;
	ssize_t	f_out;

	if (dup_stdin(lex, &f_in) == 1)
		return (1);
	if (dup_stdout(lex, &f_out) == 1)
		return (1);
	if (lex->cmd->argument[0])
	{
		if (lex->cmd->redir && (!lex->cmd->command))
			return (0);
		return (main_child2(lex));
	}
	return (0);
}

void	redirect(t_lex *lex)
{
	int		id;
	size_t	ret;

	ret = 0;
	id = fork();
	if (id < 0)
		perror("minishell");
	else if (id == 0)
	{
		ret = child(lex);
		free_child(lex);
		close_fd();
		exit(ret);
	}
	wait_stat();
	if (lex->cmd->redir->fd)
		close(lex->cmd->redir->fd[0]);
}

ssize_t	check_perm(t_lex *lex, char *str)
{
	ssize_t	i;

	i = 0;
	while (ft_strcmp(lex->cmd->redir->file[i], str) != 0)
		i++;
	if (str[0] == '/')
	{
		if (access(str, F_OK) != 0)
		{
			if (lex->cmd->redir->flag[i] == R_REDIR
				|| lex->cmd->redir->flag[i] == DR_REDIR)
				err_msg(str, "Permission denied");
			else if (lex->cmd->redir->flag[i] == L_REDIR)
				err_msg(str, "No such file or directory");
			g_exit = 1;
			return (-1);
		}
	}
	return (0);
}
