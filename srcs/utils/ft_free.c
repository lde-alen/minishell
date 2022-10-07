/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:52:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/05 15:45:52 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split_res)
{
	int	i;

	i = 0;
	while (split_res[i])
	{
		if (split_res[i])
			free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_split_baqala(char **split_res, int i)
{
	while (split_res[i])
	{
		if (split_res[i])
			free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_env_lst(t_env *lst)
{
	t_env	*tmp;
	t_env	*store;

	tmp = lst;
	while (lst->next != tmp)
	{
		store = lst->next;
		free(lst->name);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = store;
	}
	free(lst->name);
	if (lst->value)
		free(lst->value);
	free (lst);
}

void	free_cmd(t_lex *lex, t_cmd **cmd_lst)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = *cmd_lst;
	if ((*cmd_lst)->redir)
		free_redir(lex, (*cmd_lst)->redir);
	while ((*cmd_lst)->argument[i])
	{
		free((*cmd_lst)->argument[i]);
		i++;
	}
	free((*cmd_lst)->argument[i]);
	free((*cmd_lst)->argument);
	if (cmd_lst)
		(*cmd_lst) = ((*cmd_lst))->next;
	free(tmp);
}

void	free_env_kid(char **env_kid)
{
	int	i;

	i = 0;
	while (env_kid[i])
	{
		free(env_kid[i]);
		i++;
	}
	free(env_kid[i]);
	free(env_kid);
}

void	free_exec(t_exec **exec)
{
	(*exec)->i = 0;
	while ((*exec)->i < (*exec)->len)
	{
		free((*exec)->fd[(*exec)->i]);
		(*exec)->i++;
	}
	free((*exec)->fd);
	free((*exec)->id);
	free(*exec);
}

void	free_redir(t_lex *lex, t_redir *redir)
{
	(void)lex;
	size_t	i;

	if (redir->file)
	{
		i = 0;
		while (i < redir->flag_len)
		{
			free(redir->file[i]);
			if (redir->doc_arr)
			{
				free(redir->doc_arr[i]);
				redir->doc_arr[i] = NULL;
			}
			i++;
		}
		free(redir->flag);
		free(redir->file);
	}
	if (redir->doc_arr)
		free(redir->doc_arr);
	redir->doc_arr = NULL;
	if (redir->file_in)
		free(redir->file_in);
	if (redir->file_out)
		free(redir->file_out);
	if (redir->fd)
		free(redir->fd);
	free(redir);
	redir = NULL;
}

void	init_null(t_lex *lex)
{
	lex->exec->env_kid = NULL;
	lex->exec->path = NULL;
}

void	free_child(t_lex *lex)
{
	if (lex->exec->env_kid)
		free_env_kid(lex->exec->env_kid);
	if (lex->exec->path)
		free(lex->exec->path);
	if (lex->exec)
		free_exec(&lex->exec);
	if (lex->env)
		free_env_lst(lex->env);
	while (lex->cmd)
	{
		if (lex->cmd)
			free_cmd(lex, &lex->cmd);
	}
	if (lex)
		free(lex);
}
