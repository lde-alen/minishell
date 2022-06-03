/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:17:32 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/03 18:42:34 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_len(t_cmd *cmd_lst, int i)
{
	size_t	len;

	len = 0;
	while (cmd_lst->argument[i])
	{
		len++;
		i++;
	}
	return (len);
}

size_t	args_len(t_cmd *cmd_lst, int i)
{
	size_t	len;

	i = 0;
	len = 0;
	while (cmd_lst->argument[i])
	{
		len += ft_strlen(cmd_lst->argument[i]);
		i++;
	}
	return (len);
}

void	ft_join_echo(t_cmd *cmd_lst, int i, int flag)
{
	char	*str;
	int		store;

	str = "";
	store = i;
	str = (char *)malloc(sizeof(char) * (get_len(cmd_lst, i) + args_len(cmd_lst, i)));
	while (cmd_lst->argument[i])
	{
		str = ft_strjoin(str, cmd_lst->argument[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	if (flag == 0)
		ft_putendl_fd(str, 1);
	else
		ft_putstr_fd(str, 1);
}

void	ft_echo(t_cmd *cmd_lst)
{
	int			i;
	int			flag;
	size_t		j;

	i = 0;
	flag = 0;
	while (cmd_lst->argument[i])
	{
		j = 0;
		if (cmd_lst->argument[i][j] == '-')
		{
			j++;
			while (cmd_lst->argument[i][j] == 'n')
				j++;
			if (ft_strlen(cmd_lst->argument[i]) != j)
			{
				ft_join_echo(cmd_lst, i, flag);
				// while (cmd_lst->argument[i])
				// {
				// 	ft_putendl_fd(cmd_lst->argument[i], 1);
				// 	i++;
				// }
				return ;
			}
			else
				flag = 1;
		}
		else
		{
			// while (cmd_lst->argument[i])
			// {
			// 	ft_putendl_fd(cmd_lst->argument[i], 1);
			// 	i++;
			// }
			ft_join_echo(cmd_lst, i, flag);
			return ;
		}
		i++;
	}
}
