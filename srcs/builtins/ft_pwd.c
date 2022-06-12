/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:27:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/09 04:20:35 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_pwd()
{
	char *buff;

    buff = (char *)malloc(100 * sizeof(char));
    getcwd(buff,100);
    return (buff);
}

void    ft_pwd()
{
    char    *buff;

    buff = get_pwd();
    ft_putendl_fd(buff, 1);
    free(buff);
}
