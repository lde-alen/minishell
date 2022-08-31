/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:24:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/31 10:58:36 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *val)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(val, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	err_msg(t_cmd *cmd_lst, char *val, char *err)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_lst->command, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(val, 2);
	ft_putendl_fd(err, 2);
}
