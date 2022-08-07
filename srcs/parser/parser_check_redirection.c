/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/07 18:34:54 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	check if inside quotes
*/
int	check_redirections(char *str, char redirection)
{
	size_t	i;
	size_t	sr;

	i = -1;
	while (str[++i])
	{
		if (str[i] == redirection)
		{
			sr = 1;
			while (str[i] == redirection)
			{
				sr++;
				i++;
			}
			if (sr > 2)
			{
				ft_putstr_fd("ERROR:\n", 2);
				return (1);
			}
			while (str[i] == ' ')
				i++;
			if (!((str[i] > ' ' && str[i] <= '~') && str[i] != '\0'))
			{
				ft_putstr_fd("ERROR:\n", 2);
				return (1);
			}
		}
	}
	return (0);
}
