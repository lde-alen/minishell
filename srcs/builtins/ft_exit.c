/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:41:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/13 12:48:08 by asanthos         ###   ########.fr       */
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

void	check_valid(t_lex *lex, t_cmd **cmd_lst, size_t i)
{
	char	*tmp;

	check_special(lex, cmd_lst);
	if (((ft_atol((*cmd_lst)->argument[i]) > 9223372036854775807)
			&& ((*cmd_lst)->argument[i][0] == '+'
			|| (*cmd_lst)->argument[i][0] != '-'))
		|| ((ft_atol((*cmd_lst)->argument[i])
			< ft_atol("-9223372036854775808"))
		&& (*cmd_lst)->argument[i][0] == '-'))
	{
		ft_putendl_fd("exit", i);
		err_msg("exit", "numeric argument required");
		free_child(lex);
		exit(255);
	}
	else
	{
		tmp = ft_ltoa(ft_atol((*cmd_lst)->argument[i]) % 256);
		free((*cmd_lst)->argument[i]);
		(*cmd_lst)->argument[i] = ft_strdup(tmp);
		free(tmp);
	}
}

void	check_exit_val(t_lex *lex, t_cmd *cmd_lst, int *flag)
{
	*flag = 0;
	if (cmd_lst->argument[1])
	{
		if (check_str_exit(cmd_lst->argument[1]) == 0)
			check_valid(lex, &cmd_lst, 1);
		else
		{
			if (ft_strcmp(cmd_lst->argument[1], "--") == 0)
				check_sec_arg(lex, cmd_lst, flag);
			else
			{
				ft_putendl_fd("exit", 1);
				err_msg("exit", "numeric argument required");
				free_child(lex);
				exit(255);
			}
		}
	}
}

void	ft_exit(t_lex *lex, t_cmd *cmd_lst)
{
	int		flag;
	size_t	ret;

	check_exit_val(lex, cmd_lst, &flag);
	ft_putendl_fd("exit", 1);
	ret = 0;
	if (cmd_lst->argument[1] && flag == 0)
	{
		if (flag == 0)
		{
			ret = ft_atol(cmd_lst->argument[1]);
			free_child(lex);
			exit(ret);
		}
	}
	else
	{
		if (cmd_lst->argument[2])
			ret = ft_atol(cmd_lst->argument[2]);
		free_child(lex);
		exit(ret);
	}
}
