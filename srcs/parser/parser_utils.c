/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:55:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/17 18:04:26 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stage1_init(t_bool *ret, t_lex *lex)
{
	*ret = false;
	lex->sh->i = 0;
	lex->sh->euro = 0;
	lex->sh->expand_len = 0;
}

void	stage3_init(ssize_t *i, t_lex *lex)
{
	*i = 0;
	lex->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	lex->cmd->argument = NULL;
	lex->cmd->redir = NULL;
	lex->cmd->next = NULL;
}

int	check_cmd(t_lex *lex)
{
	if (!lex->cmd)
	{
		free (lex->sh->tmp_str);
		return (1);
	}
	else
		return (0);
}

int	check_tab(t_lex *lex, char **tab)
{
	if (tab == NULL)
	{
		free (lex->sh->tmp_str);
		return (1);
	}
	else
		return (0);
}

void	stage3_loop(t_lex *lex, char **tab)
{
	ssize_t	i;

	i = 0;
	while (tab[i])
	{
		lex->cmd->command = ft_strdup(tab[i]);
		ft_fill_redir(lex);
		ft_fill_arg(lex);
		if (tab[i + 1])
		{
			lex->cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
			lex->cmd = lex->cmd->next;
		}
		i++;
	}
}
