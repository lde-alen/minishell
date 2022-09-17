/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/17 15:08:59 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_env *lst, t_cmd *cmd_lst, size_t i, t_exec *exec)
{
	int	flag;
	int	status;

	flag = O_RDONLY;
	status = STDIN_FILENO;
	redirect(lst, cmd_lst, status, cmd_lst->redir->file[i], flag, exec);
}

void	redirect_out(t_env *lst, t_cmd *cmd_lst, size_t i, t_exec *exec)
{
	int	flag;
	int	status;

	flag = O_TRUNC | O_CREAT | O_WRONLY;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, status, cmd_lst->redir->file[i], flag, exec);
	// exec(lst, cmd_lst, status, cmd_lst->argument[2]);
}

void	append_out(t_env *lst, t_cmd *cmd_lst, size_t i, t_exec *exec)
{
	int	flag;
	int	status;

	flag = O_APPEND | O_WRONLY | O_CREAT;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, status, cmd_lst->redir->file[i], flag, exec);
}

size_t	get_last_delimiter(t_lex *lex)
{
	size_t	len;

	len = lex->cmd->redir->flag_len - 1;
	while (lex->cmd->redir->flag[len] != DL_REDIR)
		len--;
	return (len);
}

size_t	check_redir_type(t_lex *lex, t_exec *exec)
{
	size_t	i;

	i = 0;
	while (lex->cmd->redir->flag[i] == NOTHING)
		i++;
	if (lex->cmd->redir->flag[i] == R_REDIR)
		redirect_out(lex->env, lex->cmd, i, exec);
	else if (lex->cmd->redir->flag[i] == L_REDIR)
		redirect_in(lex->env, lex->cmd, i, exec);
	else if (lex->cmd->redir->flag[i] == DR_REDIR)
		append_out(lex->env, lex->cmd, i, exec);
	else
		return (1);
	return (0);
}

void	here_doc(t_lex *lex, t_exec *exec)
{
	int		file;
	char	*file_name;
	char	*str;
	int		status;
	size_t	i;

	(void)exec;
	file_name = "store.txt";
	file = open(file_name, O_CREAT | O_RDWR, 0777);
	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] == DL_REDIR)
		{
			str = "";
			while (ft_strcmp(str, lex->cmd->redir->file[i]) != 0)
			{
				str = readline("> ");
				if (get_last_delimiter(lex) == i
					&& ft_strcmp(str, lex->cmd->redir->file[i]) != 0)
					ft_putendl_fd(str, file);
			} 
			lex->cmd->redir->flag[i] = NOTHING;
		}
		i++;
	}
	close(file);
	status = STDIN_FILENO;
	if (check_redir_type(lex, exec) == 1)
		redirect(lex->env, lex->cmd, status, NULL, 0, exec);
		// main_child2(lex->cmd, exec);
	unlink(file_name);
	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] != DL_REDIR && get_last_delimiter(lex) == 0)
			open_file(lex->cmd->redir->file[i], O_TRUNC | O_CREAT);
		i++;
	}
}
