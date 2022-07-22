/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/04 18:59:56 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_expander(t_env *lst, t_cmd *cmd_lst, int flag)
// {
// 	t_env	*tmp;

// 	tmp = lst;
// 	while (lst->next != tmp)
// 	{
// 		if (strcmp(lst->name, ft_strchr(cmd_lst->command, cmd_lst->command[1])) == 0 && flag == 0)
// 			ft_putendl_fd(lst->value, 1);
// 		else if (flag == 1)
// 			ft_putstr_fd(lst->value, 1);
// 		lst = lst->next;
// 	}
// 	if (strcmp(lst->name, ft_strchr(cmd_lst->command, cmd_lst->command[1])) == 0 && flag == 0)
// 		ft_putendl_fd(lst->value, 1);
// 	else if (flag == 1)
// 		ft_putstr_fd(lst->value, 1);
// 	lst = tmp;
// }

void	ft_expander(t_env *lst, char *str, int flag)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp(lst->name, ft_strchr(str, str[1])) == 0 && flag == 0)
			ft_putendl_fd(lst->value, 1);
		else if (flag == 1)
			ft_putstr_fd(lst->value, 1);
		lst = lst->next;
	}
	if (strcmp(lst->name, ft_strchr(str, str[1])) == 0 && flag == 0)
		ft_putendl_fd(lst->value, 1);
	else if (flag == 1)
		ft_putstr_fd(lst->value, 1);
	lst = tmp;
}
