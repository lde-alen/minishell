/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/08 11:29:52 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_init(t_env *lst)
{
	lst->name = NULL;
	lst->value = NULL;
	lst->next = NULL;
	lst->prev = NULL;
}

void	ft_cmd_init(t_cmd *cmd_lst)
{
	cmd_lst->command = NULL;
	cmd_lst->argument = NULL;
	cmd_lst->next = NULL;
}

void	ft_exec_init(t_exec *exec)
{
	exec->fd = NULL;
	exec->id = 0;
	exec->flag = 0;
	exec->len = 0;
	exec->i = 0;
	exec->path = NULL;
	exec->env_kid = NULL;
	exec->fork_id = 0;
	exec->ret = 0;
}

void	ft_redir_init(t_lex *lex)
{
	lex->cmd->redir->left_r = 0;
	lex->cmd->redir->right_r = 0;
	lex->cmd->redir->left_dr = 0;
	lex->cmd->redir->right_dr = 0;
	lex->cmd->redir->file_in = NULL;
	lex->cmd->redir->file_out = NULL;
	lex->cmd->redir->flag_in = 0;
	lex->cmd->redir->flag_out = 0;
	lex->cmd->redir->doc_arr = NULL;
	lex->cmd->redir->fd = 0;
}
