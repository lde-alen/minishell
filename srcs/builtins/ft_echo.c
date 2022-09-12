/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:17:32 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/13 00:07:28 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_join_echo(t_cmd *cmd_lst, int i, int flag)
{
	char	*str;

	str = ft_strdup("");
	while (cmd_lst->argument[i])
	{
		str = ft_strjoin(str, cmd_lst->argument[i]);
		if (cmd_lst->argument[i + 1])
			str = ft_strjoin(str, " ");
		i++;
	}
	if (flag == 0)
		ft_putendl_fd(str, 1);
	else
		ft_putstr_fd(str, 1);
	if (str)
		free(str);
}

void	loop_str(t_cmd *cmd_lst, size_t i, size_t j)
{
	size_t	flag;

	flag = 0;
	if (cmd_lst->argument[i][j] == '-' && cmd_lst->argument[i][j + 1])
	{
		j++;
		while (cmd_lst->argument[i][j] == 'n')
			j++;
		if (ft_strlen(cmd_lst->argument[i]) != j)
		{
			ft_join_echo(cmd_lst, i, flag);
			return ;
		}
		else
			flag = 1;
	}
	else
	{
		ft_join_echo(cmd_lst, i, flag);
		return ;
	}
}

void	ft_echo(t_cmd *cmd_lst)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cmd_lst->argument[i])
	{
		j = 0;
		loop_str(cmd_lst, i, j);
		i++;
	}
	if (!cmd_lst->argument[1])
		ft_putendl_fd("", 1);
}
