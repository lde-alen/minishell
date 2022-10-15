/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/15 15:23:19 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_stage3(t_lex *lex)
{
	ssize_t	i;
	char	**tab;
	t_cmd	*tmp;

	i = 0;
	lex->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	lex->cmd->argument = NULL;
	lex->cmd->redir = NULL;
	lex->cmd->next = NULL;
	if (!lex->cmd)
	{
		free (lex->sh->tmp_str);
		return (1);
	}
	tab = splitaz(lex->sh->tmp_str, '|');
	free (lex->sh->tmp_str);
	if (tab == NULL)
	{
		free (lex->sh->tmp_str);
		return (1);
	}
	tmp = lex->cmd;
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
	free_split(tab);
	lex->cmd->next = NULL;
	lex->cmd = tmp;
	return (0);
}

/*
*/
int	parser_stage2(char *str, t_lex *lex)
{
	lex->sh->tmp_str = ft_calloc(lex->sh->input_len + 1, sizeof(char));
	if (!lex->sh->tmp_str)
		return (0);
	lex->sh->i = 0;
	lex->sh->euro = 0;
	lex->sh->j = 0;
	while (lex->sh->i < ft_strlen(str))
	{
		if (str[lex->sh->i] == '\'' || str[lex->sh->i] == '"')
			check_fill_quotes(str, str[lex->sh->i], lex);
		else if (str[lex->sh->i] == '$')
			ft_fill_expand(str, lex);
		else
			lex->sh->tmp_str[lex->sh->j] = str[lex->sh->i];
		lex->sh->i++;
		lex->sh->j++;
	}
	ft_printf("End of stage2: %s\n", lex->sh->tmp_str);
	return (0);
}

/*
	this checks for invalid synthaxes and returns 1 for errors
*/
int	parser_stage1(char *str, t_lex *lex)
{
	t_bool	ret;

	ret = false;
	lex->sh->i = 0;
	lex->sh->euro = 0;
	lex->sh->expand_len = 0;
	while (str[lex->sh->i] == ' ')
		lex->sh->i++;
	while (lex->sh->i < ft_strlen(str) && ret == false)
	{
		lex->sh->sq = 0;
		lex->sh->dq = 0;
		if (str[lex->sh->i] == '\'' || str[lex->sh->i] == '"')
			ret = check_quotes(str, str[lex->sh->i], lex);
		else if (str[lex->sh->i] == '>' || str[lex->sh->i] == '<')
			ret = check_redirections(str, lex);
		else if (str[lex->sh->i] == '|')
			ret = check_p(str, lex);
		else if (str[lex->sh->i] == '$')
			ft_check_expand(str, lex);
		lex->sh->i++;
	}
	lex->sh->input_len = lex->sh->i + lex->sh->expand_len;
	if (ret == false)
		return (0);
	else
		return (1);
}

int	ft_parse(char *str, t_lex *lex)
{
	if (!str)
		return (1);
	lex->sh = (t_sh *)malloc(sizeof(t_sh));
	if (!lex->sh)
		return (1);
	if (parser_stage1(str, lex) == 0)
	{
		parser_stage2(str, lex);
		parser_stage3(lex);
		free(lex->sh);
		ft_printf("~~~~~~ End of Parsing succes. ~~~~~~\n\n");
		return (0);
	}
	free(lex->sh);
	ft_printf("~~~~~~ End of Parsing with error. ~~~~~~\n\n");
	return (1);
}
