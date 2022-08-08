/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 19:42:36 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
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
