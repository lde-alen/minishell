/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:20:37 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/01 17:48:44 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_unset(t_env *lst, t_cmd *cmd_lst)
{
    int i;
    t_env *tmp;

    i = 0;
    tmp = lst;
    while (cmd_lst->argument[i])
    {
        while (lst->next != tmp)
        {
            if (strcmp(cmd_lst->argument[i], lst->name) == 0)
            {
                printf("%s %s\n", cmd_lst->argument[i], lst->name);
                lst->prev->next = lst->next;
                lst->next->prev = lst->prev;
                free(lst);
            }
            lst = lst->next;
        }
        if (strcmp(cmd_lst->argument[i], lst->name) == 0)
        {
            printf("%s %s\n", cmd_lst->argument[i], lst->name);
            lst->prev->next = lst->next;
            lst->next->prev = lst->prev;
            free(lst);
        }
        i++;
    }
    lst = tmp;
}
