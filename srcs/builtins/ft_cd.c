/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:13:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/09 04:22:24 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env   *search_pwd(t_env *lst)
{
    t_env   *tmp;

    tmp = lst;
    while (lst->next != tmp)
    {
        if (strcmp(lst->name, "PWD") == 0)
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}

void ft_cd(t_cmd *cmd_lst, t_env *lst)
{
    char    *buff;
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
    buff = get_pwd();
    (search_pwd(lst))->value = buff;
    // free(buff);
}
