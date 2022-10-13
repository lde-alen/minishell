/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:03:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/13 12:27:51 by asanthos         ###   ########.fr       */
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
