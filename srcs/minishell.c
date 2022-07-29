/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/05/30 11:13:36 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	shell_prompt(env);
	return (0);
}
