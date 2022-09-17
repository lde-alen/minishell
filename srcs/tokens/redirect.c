/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/16 12:30:40 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_env *lst, t_cmd *cmd_lst, size_t i)
{
	int	flag;
	int	status;

	flag = O_RDONLY;
	status = STDIN_FILENO;
	redirect(lst, cmd_lst, flag, status, i);
}

void	redirect_out(t_env *lst, t_cmd *cmd_lst, size_t i)
{
	int	flag;
	int	status;

	flag = O_TRUNC | O_CREAT | O_WRONLY;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status, i);
	// exec(lst, cmd_lst, status, cmd_lst->argument[2]);
}

void	append_out(t_env *lst, t_cmd *cmd_lst, size_t i)
{
	int	flag;
	int	status;

	flag = O_APPEND | O_WRONLY | O_CREAT;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status, i);
}

size_t	get_last_delimiter(t_lex *lex)
{
	size_t	len;

	len = lex->cmd->redir->flag_len - 1;
	while (lex->cmd->redir->flag[len] != DL_REDIR)
		len--;
	return (len);
}

void	check_redir_type(t_lex *lex)
{
	size_t	i;

	i = 0;
	while (lex->cmd->redir->flag[i] == NOTHING)
		i++;
	if (lex->cmd->redir->flag[i] == R_REDIR)
		redirect_out(lex->env, lex->cmd, i);
	else if (lex->cmd->redir->flag[i] == L_REDIR)
		redirect_in(lex->env, lex->cmd, i);
	else if (lex->cmd->redir->flag[i] == DR_REDIR)
		append_out(lex->env, lex->cmd, i);
}

void	here_doc(t_lex *lex)
{
	int		file;
	char	*file_name;
	char	*str;
	// int		status;
	size_t	i;

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
		}
		i++;
	}
	close(file);
	// status = STDIN_FILENO;
	check_redir_type(lex);
	// exec(lex->env, lex->cmd, status, file_name);
	unlink(file_name);
	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] != DL_REDIR && get_last_delimiter(lex) == 0)
			open_file(lex->cmd->redir->file[i], O_TRUNC | O_CREAT);
		i++;
	}
}

// void	here_doc(t_env *lst, t_cmd *cmd_lst)
// {
// 	int		file;
// 	int		status;
// 	char	*str;
// 	char	*file_name;

// 	file_name = "store.txt";
// 	file = open(file_name, O_CREAT | O_RDWR, 0777);
// 	str = "";
// 	// signal(SIGINT, sig_handler);
// 	while (ft_strcmp(str, cmd_lst->argument[2]) != 0)
// 	{
// 		str = readline("> ");
// 		if (ft_strcmp(str, cmd_lst->argument[2]) != 0)
// 			ft_putendl_fd(str, file);
// 	}
// 	close(file);
// 	status = STDIN_FILENO;
// 	exec(lst, cmd_lst, status, file_name);
// 	unlink(file_name);
// }
