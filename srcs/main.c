/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:00:41 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/31 13:46:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		if (*env == NULL)
		{
			ft_putendl_fd("Error: ENV = NULL", 2);
			return (0);
		}
		else
			minishell(ac, av, env);
	}
	else
		ft_putendl_fd("Too many arguments!!\n\nRun with:\n./minishell", 2);
	return (0);
}
