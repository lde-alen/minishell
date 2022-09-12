/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:01:52 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 20:02:11 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expander(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	if (ft_strcmp(str, "$?") == 0)
		ft_printf("%d\n", g_exit);
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
