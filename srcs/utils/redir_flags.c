/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:17:15 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 16:18:18 by asanthos         ###   ########.fr       */
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

void	check_redir_type(t_lex *lex)
{
	if (lex->cmd->redir->left_r > lex->cmd->redir->left_dr)
		redirect_in(lex,
			ft_strdup(lex->cmd->redir->file[lex->cmd->redir->left_r]));
	else if (lex->cmd->redir->left_dr > lex->cmd->redir->left_r)
	{
		dup_doc(lex);
		lex->cmd->redir->file_in = NULL;
		lex->cmd->redir->flag_in = -1;
	}
	else
		redirect_in(lex, NULL);
	if (lex->cmd->redir->right_r > lex->cmd->redir->right_dr)
		redirect_out(lex,
			ft_strdup(lex->cmd->redir->file[lex->cmd->redir->right_r]));
	else if (lex->cmd->redir->right_dr > lex->cmd->redir->right_r)
		append_out(lex,
			ft_strdup(lex->cmd->redir->file[lex->cmd->redir->right_dr]));
	else
		redirect_out(lex, NULL);
}
