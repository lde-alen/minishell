/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/07 05:31:22 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	check if inside quotes
*/
int	check_redirections(char *str, char *redirection)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (2);
		if (str[i] == redirection[0] && (str[i + (ft_strlen(redirection) - 1)] == redirection[0]))
		{
			j = ft_strlen(redirection) + i;
			if (!str[j])
			{
				ft_putstr_fd("Error: Invalid synthax.\n", 2);
				return (1);
			}
			while (str[j] == ' ')
				j++;
			if (!(str[j] > ' ' && str[j] <= '~') || str[j] == '>' || str[j] == '<')
			{
				ft_putstr_fd("Error: Invalid synthax.\n", 2);
				return (1);
			}
			i = j - 1;
		}
	}
	return (0);
}
