/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/02 13:31:26 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_unset(t_env *lst, t_cmd *cmd_lst)
{
    int i;
    t_env *tmp;
    t_env *tmp2;

    i = 0;
    tmp = lst;
    while (cmd_lst->argument[i])
    {
        while (lst->next != tmp)
        {
            if (strcmp(cmd_lst->argument[i], lst->name) == 0)
            {
                tmp2 = lst;
                lst->prev->next = lst->next;
                lst->next->prev = lst->prev;
                free(tmp2);
            }
            lst = lst->next;
        }
        if (strcmp(cmd_lst->argument[i], lst->name) == 0)
        {
            tmp2 = lst;
            lst->prev->next = lst->next;
            lst->next->prev = lst->prev;
            free(tmp2);
        }
        i++;
    }
    lst = tmp;
}
