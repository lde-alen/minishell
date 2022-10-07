/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/07 12:07:03 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_doc(t_lex *lex)
{
	int	id;

	lex->cmd->redir->fd = (int *)malloc(sizeof(int) * 2);
	pipe(lex->cmd->redir->fd);
	id = fork();
	if (id < 0)
		perror("dead");
	if (id == 0)
	{
		dup2(lex->cmd->redir->fd[1], STDOUT_FILENO);
		close(lex->cmd->redir->fd[1]);
		close(lex->cmd->redir->fd[0]);
		ft_putendl_fd(lex->cmd->redir->doc_arr[lex->cmd->redir->left_dr], 1);
		free_child(lex);
		exit(0);
	}
	wait_stat();
	close(lex->cmd->redir->fd[1]);
}

size_t	main_child2(t_lex *lex)
{
	size_t	err;

	if (lex->exec->flag == 1)
	{
		lex->exec->flag = 2;
		exec_builtin(lex);
		return (0);
	}
	err = check_type(lex->cmd, &lex->exec);
	if (err != 0)
		return (err);
	return (exec_child(lex->cmd, lex-> exec));
}

size_t	first_child(t_lex *lex, t_exec *exec)
{
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2");
	close(exec->fd[exec->i][1]);
	if (lex->cmd->redir)
	{
		redir(lex);
		return (0);
	}
	return (main_child2(lex));
}

size_t	last_child(t_lex *lex, t_exec *exec)
{
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2ME");
	close(exec->fd[(exec->i - 1)][0]);
	if (lex->cmd->redir)
	{
		redir(lex);
		return (0);
	}
	return (main_child2(lex));
}

size_t	mid_kid(t_lex *lex, t_exec *exec)
{
	close(exec->fd[exec->i][0]);
	if (dup2(exec->fd[(exec->i - 1)][0], STDIN_FILENO) < 0)
		perror("dup2_Mid1");
	if (dup2(exec->fd[exec->i][1], STDOUT_FILENO) < 0)
		perror("dup2_mid2");
	close(exec->fd[(exec->i - 1)][0]);
	close(exec->fd[exec->i][1]);
	if (lex->cmd->redir)
	{
		redir(lex);
		return (0);
	}
	return (main_child2(lex));
}
