 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:41:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/03 12:57:59 by asanthos         ###   ########.fr       */
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

void	exit_error(t_cmd *cmd_lst)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(cmd_lst->argument[1], 2);
	ft_putendl_fd(" numeric argument required", 2);
}

void	check_valid(t_cmd **cmd_lst, size_t i)
{
	char	*tmp;

	if (((ft_atol((*cmd_lst)->argument[i]) > 9223372036854775807)
			&& ((*cmd_lst)->argument[i][0] == '+'
			|| (*cmd_lst)->argument[i][0] != '-'))
		|| ((ft_atol((*cmd_lst)->argument[i])
			< ft_atol("-9223372036854775808"))
		&& (*cmd_lst)->argument[i][0] == '-'))
	{
		ft_putendl_fd("exit", i);
		exit_error(*cmd_lst);
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

void	ft_exit(t_lex *lex, t_cmd *cmd_lst)
{
	int		flag;
	size_t	ret;

	flag = 0;
	if (cmd_lst->argument[1])
	{
		if (check_str_exit(cmd_lst->argument[1]) == 0)
			check_valid(&cmd_lst, 1);
		else
		{
			if (ft_strcmp(cmd_lst->argument[1], "--") == 0)
			{
				flag = 1;
				check_valid(&cmd_lst, 2);
			}
			else	
			{
				ft_putendl_fd("exit", 1);
				exit_error(cmd_lst);
				free_child(lex);
				exit(255);
			}
		}
	}
	ft_putendl_fd("exit", 1);
	if (cmd_lst->argument[1] && flag == 0)
	{
		if (flag == 0)
		{
			ret = ft_atol(cmd_lst->argument[1]);
			free_child(lex);
			exit(ret);
		}
		else if (cmd_lst->argument[2] && flag == 1)
		{
			ret = ft_atol(cmd_lst->argument[2]);
			free_child(lex);
			exit(ret);
		}
	}
	else
	{
		free_child(lex);
		exit(0);
	}
}
