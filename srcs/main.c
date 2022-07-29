/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:00:41 by lde-alen          #+#    #+#             */
/*   Updated: 2022/06/03 11:11:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
