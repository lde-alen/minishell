/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:21 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/20 16:41:28 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_arg(char ***argument, char *str)
{
	if (!argument)
		return (-1);
	*argument = ft_split(str, ' ');
	return (1);
}

int	ft_fill_cmd(char **command, char **argument)
{
	if (!argument[0])
		return (-1);
	*command = argument[0];
	return (1);
}
