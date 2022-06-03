/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:27:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/03 15:55:00 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd()
{
	char *buff;

    buff = (char *)malloc(100 * sizeof(char));
    getcwd(buff,100);
    ft_putendl_fd(buff, 1);
    free(buff);
}
