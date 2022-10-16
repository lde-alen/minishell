/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimz_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:41:35 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/16 13:52:43 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	checkz(char *str, t_lex *lex)
{
	if (ft_parse(str, lex) == 0)
	{
		if (lex->cmd)
		{
			if (lex->cmd->argument)
			{
				if (!lex->cmd->command && !lex->cmd->next
					&& !lex->cmd->redir)
				{
					ft_printf("FREE INVALID\n");
					while (lex->cmd)
						free_cmd(&lex->cmd);
					return ;
				}
				trimaz(lex);
				exec_sys(lex);
			}
			else
				free_cmd(&lex->cmd);
		}
	}
}

static void	mini_free(t_lex *lex)
{
	if (lex->cmd)
		if (lex->cmd->redir)
			free_child(lex);
	free(lex->cmd);
	free_env_lst(lex->env);
	free (lex);
}

void	mini_loop(t_lex *lex, char *str)
{
	if (str)
	{
		if (ft_strlen(str) >= 1)
		{
			add_history(str);
			checkz(str, lex);
		}
	}
	else
	{
		mini_free(lex);
		exit(g_exit);
	}
}
