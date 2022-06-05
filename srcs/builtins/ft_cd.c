/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:13:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/05 07:47:16 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_cd(t_cmd *cmd_lst)
{
    // int i;

    // i = 0;
    // if (!cmd_lst->argument[0] || cmd_lst->argument[0] == '~')
    // {
    //     while (1)
    //     {
    //         if ()
    //     }
    //     chdir("Desktop");
    // }
    chdir(cmd_lst->argument[0]);
}
