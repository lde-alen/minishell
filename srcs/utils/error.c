/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:24:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 19:54:25 by lde-alen         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_lst->command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(val, 2);
	ft_putendl_fd(err, 2);
}
