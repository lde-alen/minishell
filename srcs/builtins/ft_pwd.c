/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:27:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 16:14:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd()
{
	char	*buff;

	buff = (char *)malloc(100 * sizeof(char));
	getcwd(buff,100);
	return (buff);
}

void	ft_pwd(t_env *lst)
{
	char	*buff;

	buff = NULL;
	buff = get_pwd();
	if (ft_strcmp(search_pwd(lst)->value, "//") == 0)
		ft_putendl_fd("//", 1);
	else
		ft_putendl_fd(buff, 1);
	free(buff);
}
