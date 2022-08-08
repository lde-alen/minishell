/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:31:56 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/08 19:30:29 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_char_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

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
