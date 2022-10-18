/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:41:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/19 03:15:39 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cp_till_prev(char *arg)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * ft_strlen(arg));
	while (arg[i + 1])
	{
		dest[i] = arg[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_str_exit(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_valid(t_lex *lex, t_cmd **cmd_lst, size_t i)
{
	check_plus_minus(lex, cmd_lst, i);
	if (check_special(cmd_lst) == 1)
		return (1);
	if (((ft_atol((*cmd_lst)->argument[i]) > 9223372036854775807)
			&& ((*cmd_lst)->argument[i][0] == '+'
			|| (*cmd_lst)->argument[i][0] != '-'))
		|| ((ft_atol((*cmd_lst)->argument[i])
			< ft_atol("-9223372036854775808"))
		&& (*cmd_lst)->argument[i][0] == '-'))
	{
		exit_msg(lex);
		g_exit = 255;
		exit(g_exit);
	}
	else
		ft_check_valid_utils(lex, cmd_lst, i);
	return (0);
}

int	check_exit_val(t_lex *lex, t_cmd *cmd_lst, int *flag)
{
	*flag = 0;
	if (cmd_lst->argument[1])
	{
		if (check_str_exit(cmd_lst->argument[1]) == 0)
		{
			if (check_valid(lex, &cmd_lst, 1) == 1)
				return (1);
		}
		else
		{
			if (ft_strcmp(cmd_lst->argument[1], "--") == 0)
			{
				if (check_sec_arg(lex, cmd_lst, flag) == 1)
					return (1);
			}
			else
			{
				exit_msg(lex);
				g_exit = 255;
				exit(g_exit);
			}
		}
	}
	return (0);
}

void	ft_exit(t_lex *lex, t_cmd *cmd_lst)
{
	int		flag;

	if (check_exit_val(lex, cmd_lst, &flag) == 1)
		return ;
	ft_putendl_fd("exit", 1);
	if (!cmd_lst->argument[1])
		g_exit = 0;
	else if (cmd_lst->argument[1] && flag == 0)
	{
		if (flag == 0)
			g_exit = ft_atol(cmd_lst->argument[1]);
	}
	else
	{
		if (cmd_lst->argument[2])
			g_exit = ft_atol(cmd_lst->argument[2]);
	}
	free_child(lex);
	exit(g_exit);
}
