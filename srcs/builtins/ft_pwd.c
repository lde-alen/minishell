/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:27:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/03 12:11:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_env *lst)
{
	t_env   *tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp("PWD", lst->name) == 0)
		{
			ft_putendl_fd(lst->value, 1);
			break ;
		}
		lst = lst->next;
	}
}
