/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:44:32 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/08 19:56:03 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_expand(char *str, t_sh *sh, t_env *env)
{
	size_t	i;

	i = 0;
	ft_printf("euro = %d\n", sh->euro);
	while (str[i])
	{
		ft_printf("str[i] = %c\n", str[i]);
		if (str[i] == '$')
			print_list_env(env);
		i++;
	}
	return (0);
}
