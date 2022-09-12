/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:srcs/utils/ft_print.c
/*   Created: 2022/07/29 19:31:56 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/03 16:53:38 by lde-alen         ###   ########.fr       */
========
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/10 19:13:37 by asanthos         ###   ########.fr       */
>>>>>>>> origin/alka:srcs/utils/expand.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

<<<<<<<< HEAD:srcs/utils/ft_print.c
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
========
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
>>>>>>>> origin/alka:srcs/utils/expand.c
}
