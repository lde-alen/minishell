/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:36:49 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/31 12:38:41 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args(t_env *head, t_cmd *cmd)
{
	if (ft_strcmp(cmd->argument[1], "PWD") == 0)
	{
		if (cmd->argument[2])
		{
			g_exit = 1;
			ft_putendl_fd("usage: pwd [-L | -P]", 2);
		}
		else
			ft_putendl_fd(search_pwd(head)->value, 1);
	}
	else
	{
		g_exit = 127;
		err_msg(cmd, cmd->argument[1], ": No such file or directory");
	}
}

void	print_list_env(t_env *head, t_cmd *cmd)
{
	t_env	*tmp;

	g_exit = 0;
	if (cmd->argument[1])
		check_args(head, cmd);
	else
	{
		tmp = head;
		while (head->next != tmp)
		{
			if (head->value != NULL)
				ft_printf("%s=%s\n", head->name, head->value);
			head = head->next;
		}
		if (head->value != NULL)
			ft_printf("%s=%s\n", head->name, head->value);
		head = tmp;
	}
}

void	print_lst(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (lst->value != NULL)
			ft_printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
		else
			ft_printf("declare -x %s\n", lst->name);
		lst = lst->next;
	}
	if (lst->value != NULL)
		ft_printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
	else
		ft_printf("declare -x %s\n", lst->name);
}