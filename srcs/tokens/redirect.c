/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/14 15:08:49 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_RDONLY;
	status = STDIN_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

void	redirect_out(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_TRUNC | O_CREAT | O_WRONLY;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status);
	exec(lst, cmd_lst, status, cmd_lst->argument[2]);
}

void	append_out(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_APPEND | O_WRONLY | O_CREAT;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

size_t	get_last_delimiter(t_lex *lex)
{
	size_t	len;

	len = lex->cmd->redir->flag_len;
	while (lex->cmd->redir->flag[len] != DL_REDIR)
		len--;
	return (len);
}

void	here_doc(t_lex *lex)
{
	int		file;
	char	*file_name;
	char	*str;
	int		status;
	size_t	i;

	file_name = "store.txt";
	file = open(file_name, O_CREAT | O_RDWR, 0777);
	str = "";
	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] != NOTHING)
		{
			while (ft_strcmp(str, lex->cmd->redir->file[i]) != 0)
			{
				str = readline("> ");
				if (get_last_delimiter(lex) == i)
				{
					if (ft_strcmp(str, lex->cmd->redir->file[i]) != 0)
						ft_putendl_fd(str, file);
				}
			}
			lex->cmd->redir->file[i] = NOTHING;
		}
		i++;
	}
	close(file);
	status = STDIN_FILENO;
	exec(lex->env, lex->cmd, status, file_name);
	unlink(file_name);
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
