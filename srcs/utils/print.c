/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:36:49 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/06 20:28:09 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (head->next != tmp)
	{
		if (head->value != NULL)
			ft_printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	if (head->value != NULL)
		ft_printf("%s=%s\n", head->name, head->value);
	head = tmp;
}

void	print_lst(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;

	while (lst->next != tmp)
	{
		if (lst->value != NULL)
			ft_printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
		else
			ft_printf("declare -x %s\n", lst->name);
		lst = lst->next;
	}
	if (lst->value != NULL)
		ft_printf("declare -x %s=\"%s\"\n", lst->name, lst->value);
	else
		ft_printf("declare -x %s\n", lst->name);
}
