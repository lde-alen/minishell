/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 05:23:09 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_init(t_env *lst)
{
	lst->env_str = NULL;
	lst->name = NULL;
	lst->value = NULL;
	lst->next = NULL;
	lst->prev = NULL;
}

void	ft_cmd_init(t_cmd *cmd_lst)
{
	cmd_lst->command = NULL;
	cmd_lst->argument = NULL;
	cmd_lst->o_token = NULL;
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
}
