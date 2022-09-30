/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:45:02 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/30 13:13:13 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_type(t_cmd *cmd_lst, t_exec **exec)
{
	struct stat	path_stat;
	int			stat_ch;

	stat_ch = stat(cmd_lst->argument[0], &path_stat);
	if (stat_ch == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (ft_strchr(cmd_lst->argument[0], '/') == 0)
			{
				err_msg(cmd_lst, "", "command not found");
				g_exit = 127;
			}
			else
			{
				err_msg(cmd_lst, "", "is a directory");
				g_exit = 126;
			}
			return (g_exit);
		}
	}
	if ((ft_strchr(cmd_lst->argument[0], '/') == 0 && (*exec)->path == NULL)
		|| (!cmd_lst->argument[0]))
	{
		err_msg(cmd_lst, "", "command not found");
		g_exit = 127;
		return (g_exit);
	}
	if ((*exec)->path == NULL)
		(*exec)->path = ft_strdup(cmd_lst->command);
	return (0);
}

void	dup_doc(t_lex *lex)
{
	lex->cmd->redir->fd = (int *)malloc(sizeof(int) * 2);
	pipe(lex->cmd->redir->fd);
	int id = fork();
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
	wait(&g_exit);
	close(lex->cmd->redir->fd[1]);
}

size_t	exit_stat(int err)
{
	perror("minishell");
	ft_printf("Errno: %d\n", err);	
	if (errno == 2)
	{
		g_exit = 127;
		return (g_exit);
	}
	else if (errno == 13 || errno == 20)
	{
		g_exit = 126;
		return (g_exit);
	}
	return (0);
}

size_t	exec_child(t_cmd *cmd_lst, t_exec *exec)
{
	int		ret;

	ret = execve(exec->path, cmd_lst->argument, exec->env_kid);
	if (ret < 0)
		return (exit_stat(errno));
	return (0);
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
	return (exec_child(lex->cmd,lex-> exec));
}

t_bool	check_here_doc(t_lex *lex)
{
	size_t	i;

	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] == DL_REDIR)
			return (true);
		i++;
	}
	return (false);
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

void	 check_pos(t_lex *lex, t_exec *exec)
{
	size_t	ret;

	if (exec->i == 0)
		ret = first_child(lex, exec);
	else if (exec->i + 1 == exec->len) 
		ret = last_child(lex, exec);
	else
		ret = mid_kid(lex, exec);
	free_child(lex);
	exit(ret);
}
