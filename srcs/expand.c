/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/30 03:32:47 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expander(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp(lst->name, ft_strchr(str, str[1])) == 0)
			ft_putendl_fd(lst->value, 1);
		lst = lst->next;
	}
	if (strcmp(lst->name, ft_strchr(str, str[1])) == 0)
		ft_putendl_fd(lst->value, 1);
	lst = tmp;
}
