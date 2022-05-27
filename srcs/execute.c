/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/27 17:48:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(char *str, char *env[])
{
	if (str[0] == '$')
		ft_expander(str, env);
	if (strncmp(str, "echo", 4) == 0)
		ft_echo(str);
}
