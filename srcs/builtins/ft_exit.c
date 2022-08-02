/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 03:41:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/02 05:37:39 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_exit(t_cmd *cmd_lst)
// {
// 	ft_putendl("exit", 1);
// 	if (cmd_lst->argument[1])
// 	{
// 		if (cmd_lst->argument[1] > 9223372036854775807)
// 		{
// 			ft_putstr_fd("bash: exit: ", 2);
// 			ft_putstr_fd(cmd_lst->argument[1], 2);
// 			ft_putendl_fd("numeric argument required", 2);
// 		}
// 		exit(cmd_lst->argument[1]);
// 	}
// 	exit(0);
// }
