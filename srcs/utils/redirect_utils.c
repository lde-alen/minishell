/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 10:07:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 11:54:55 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

user_ssize_t	dup_stdin(t_lex *lex, ssize_t *f_in)
{
	if (lex->cmd->redir->file_in != NULL)
	{
		*f_in = open_file(lex, lex->cmd->redir->file_in,
				lex->cmd->redir->flag_in);
		if (dup2(*f_in, STDIN_FILENO) < 0 || *f_in < 0)
		{
			g_exit = 1;
			perror("minishell");
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
			perror("minishell");
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

	if (dup_stdin(lex, &f_in) == 1 || dup_stdout(lex, &f_out) == 1)
		return (1);
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
				err_msg(lex->cmd, str, "Permission denied");
			else if (lex->cmd->redir->flag[i] == L_REDIR)
				err_msg(lex->cmd, str, "No such file or directory");
			g_exit = 1;
			return (-1);
		}
	}
	return (0);
}

ssize_t	open_file(t_lex *lex, char *str, int flag)
{
	int		file;

	if (check_perm(lex, str) == -1)
		return (-1);
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
