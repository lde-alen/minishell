/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:00:41 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/11 20:46:49 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		if (*env == NULL)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(av[0], 2);
			ft_putendl_fd(": ENV = NULL", 2);
			return (0);
		}
		else
			minishell(env);
	}
	else
		ft_putendl_fd("Too many arguments!!\n\nRun with:\n./minishell", 2);
	return (0);
}
