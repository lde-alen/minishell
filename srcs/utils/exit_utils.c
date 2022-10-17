/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:03:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/15 14:32:25 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_sec_arg(t_lex *lex, t_cmd *cmd_lst, int *flag)
{
	if (cmd_lst->argument[2])
	{
		if (!cmd_lst->argument[3])
		{
			*flag = 1;
			check_valid(lex, &cmd_lst, 2);
		}
		else
		{
			err_msg("exit", "too many arguments");
			free_child(lex);
			exit(1);
		}
	}
}

void	check_plus_minus(t_lex *lex, t_cmd **cmd_lst, size_t i)
{
	if (ft_strcmp((*cmd_lst)->argument[i], "+") == 0
		|| ft_strcmp((*cmd_lst)->argument[i], "-") == 0)
	{
		ft_putendl_fd("exit", i);
		err_msg("exit", "numeric argument required");
		free_child(lex);
		g_exit = 1;
		exit(g_exit);
	}
}

void	check_special(t_lex *lex, t_cmd **cmd_lst)
{
	if (ft_strcmp((*cmd_lst)->argument[1], "--") != 0)
	{
		if ((*cmd_lst)->argument[2])
		{
			err_msg("exit", "too many arguments");
			free_child(lex);
			exit(1);
		}
	}
}
