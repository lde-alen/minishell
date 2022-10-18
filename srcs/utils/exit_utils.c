/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:03:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/19 03:16:37 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sec_arg(t_lex *lex, t_cmd *cmd_lst, int *flag)
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
			g_exit = 1;
			return (1);
		}
	}
	return (0);
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

int	check_special(t_cmd **cmd_lst)
{
	if (ft_strcmp((*cmd_lst)->argument[1], "--") != 0)
	{
		if ((*cmd_lst)->argument[2])
		{
			err_msg("exit", "too many arguments");
			g_exit = 1;
			return (1);
		}
	}
	return (0);
}

void	exit_msg(t_lex *lex)
{
	ft_putendl_fd("exit", 2);
	err_msg("exit", "numeric argument required");
	free_child(lex);
}

void	ft_check_valid_utils(t_lex *lex, t_cmd **cmd_lst, size_t i)
{
	char	*tmp;

	if (ft_atol((*cmd_lst)->argument[i]) == 0
		|| (*cmd_lst)->argument[i] == (void *) '\0')
	{
		exit_msg(lex);
		g_exit = 255;
		exit(g_exit);
	}
	tmp = ft_ltoa(ft_atol((*cmd_lst)->argument[i]) % 256);
	free((*cmd_lst)->argument[i]);
	(*cmd_lst)->argument[i] = ft_strdup(tmp);
	free(tmp);
}
