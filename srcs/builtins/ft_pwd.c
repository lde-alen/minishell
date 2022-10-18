/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:27:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 23:59:52 by lde-alen         ###   ########.fr       */
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
	if (search_env(lst, "PWD") && ft_strcmp(
			search_env(lst, "PWD")->value, "//") == 0)
		ft_putendl_fd("//", 1);
	else
		ft_putendl_fd(buff, 1);
	if (buff)
		free(buff);
}
