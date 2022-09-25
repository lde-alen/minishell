/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:27:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/25 18:58:39 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	return (ft_strdup(buff));
}

void	ft_pwd(t_env *lst)
{
	char	*buff;

	buff = NULL;
	buff = get_pwd();
	if (ft_strcmp(search_env(lst, "PWD")->value, "//") == 0)
		ft_putendl_fd("//", 1);
	else
		ft_putendl_fd(buff, 1);
	free(buff);
}
