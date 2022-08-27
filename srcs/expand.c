/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/14 13:42:22 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern int g_exit;

void	ft_expander(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	// if (ft_strcmp(str, ))
	// 	ft_putendl_fd((char*)&g_exit, 1);
	while (lst->next != tmp)
	{
		if (ft_strcmp(lst->name, ft_strchr(str, str[1])) == 0)
			ft_putendl_fd(lst->value, 1);
		lst = lst->next;
	}
	if (ft_strcmp(lst->name, ft_strchr(str, str[1])) == 0)
		ft_putendl_fd(lst->value, 1);
	lst = tmp;
}
