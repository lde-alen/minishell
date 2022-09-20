/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/20 05:02:52 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_lex *lex, char *file)
{
	lex->cmd->redir->flag_in = O_RDONLY;
	lex->cmd->redir->file_in = file;
}

void	redirect_out(t_lex *lex, char *file)
{
	lex->cmd->redir->flag_out = O_TRUNC | O_CREAT | O_WRONLY;
	lex->cmd->redir->file_out = file;
}

void	append_out(t_lex *lex, char *file)
{
	lex->cmd->redir->flag_out = O_APPEND | O_WRONLY | O_CREAT;
	lex->cmd->redir->file_out = file;
}

size_t	get_last_delimiter(t_lex *lex)
{
	size_t	len;

	len = lex->cmd->redir->flag_len - 1;
	while (lex->cmd->redir->flag[len] != DL_REDIR)
		len--;
	return (len);
}

void	check_redir_type(t_lex *lex, t_exec *exec)
{
	if (lex->cmd->redir->left_r > lex->cmd->redir->left_dr)
		redirect_in(lex, lex->cmd->redir->file[lex->cmd->redir->left_r]);
	else if (lex->cmd->redir->left_dr > lex->cmd->redir->left_r)
		redirect_in(lex, "store.txt");
	else
		redirect_in(lex, NULL);
	if (lex->cmd->redir->right_r > lex->cmd->redir->right_dr)
		redirect_out(lex, lex->cmd->redir->file[lex->cmd->redir->right_r]);
	else if (lex->cmd->redir->right_dr > lex->cmd->redir->right_r)
		append_out(lex, lex->cmd->redir->file[lex->cmd->redir->right_dr]);
	else
		redirect_out(lex, NULL);
	redirect(lex, exec);
}

ssize_t	find_redir_in(t_lex *lex, size_t type)
{
	int	i;

	i = lex->cmd->redir->flag_len;
	while (i >= 0)
	{
		if (lex->cmd->redir->flag[i - 1] == type)
			return (i - 1);
		i--;
	}
	return (-1);
}

void	here_doc(t_lex *lex, t_exec *exec)
{
	int		file;
	char	*file_name;
	char	*str;
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
	check_redir_type(lex, exec);
	unlink(file_name);
}
