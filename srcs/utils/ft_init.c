/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 20:22:23 by lde-alen         ###   ########.fr       */
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
}
