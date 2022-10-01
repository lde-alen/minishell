/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:45:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 12:46:33 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_lex *lex, t_exec *exec)
{
	char	*val;
	int		shl_val;

	if (exec->path != NULL && ft_strcmp(exec->path, "./minishell")
		== 0 && search_env(lex->env, "SHLVL") != NULL)
	{
		val = search_env(lex->env, "SHLVL")->value;
		if (!val)
			val = ft_strdup("1");
		else
		{
			shl_val = ft_atoi(val);
			free(val);
			if (shl_val < 0)
				val = ft_strdup("0");
			else if (shl_val < 999)
				val = ft_itoa(shl_val + 1);
			else
			{
				err_msg(lex->cmd, "warning",
					"shell level too high, resetting to 1");
				val = ft_strdup("1");
			}
		}
	}
}
