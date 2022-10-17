/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:24:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/09 14:18:05 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *val)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(val, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	err_msg(char *val, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(val, 2);
	if (ft_strcmp(val, "") != 0)
		ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}
