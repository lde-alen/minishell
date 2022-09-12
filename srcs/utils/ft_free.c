/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:52:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 23:40:45 by lde-alen         ###   ########.fr       */
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

void	free_cmd(t_cmd **cmd_lst)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = *cmd_lst;
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

void	free_child(t_exec *exec, t_env *lst, t_cmd *cmd_lst)
{
	if (exec->env_kid)
		free_env_kid(exec->env_kid);
	if (exec->path)
		free(exec->path);
	if (exec)
		free_exec(&exec);
	if (lst)
		free_env_lst(lst);
	if (cmd_lst)
		free_cmd(&cmd_lst);
}
