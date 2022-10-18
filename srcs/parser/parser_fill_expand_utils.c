/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_expand_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:00:42 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 00:35:39 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	question_assist(char **name, char *ascii_exit, t_lex *lex, char *str)
{
	*name = ft_append_char(*name, str[lex->sh->i]);
	lex->sh->expand_len += get_expand_len(*name, lex->env, 1);
	ascii_exit = ft_itoa(g_exit);
	lex->sh->j += ft_strlen(ascii_exit);
	ft_strjustcat(lex->sh->tmp_str, ascii_exit);
	if (ascii_exit)
		free(ascii_exit);
	lex->sh->i++;
}

void	special_c(t_lex *lex, char **name, char *str)
{
	lex->sh->i--;
	while (str[lex->sh->i])
	{
		*name = ft_append_char(*name, str[lex->sh->i]);
		lex->sh->i++;
	}
	lex->sh->i--;
	ft_strjustcat(lex->sh->tmp_str, *name);
}

void	setup_expand(t_lex *lex, char **name, char *str)
{
	while (str[lex->sh->i] && str[lex->sh->i] != '$'
		&& ft_isalnum(str[lex->sh->i]) == 1)
	{
		*name = ft_append_char(*name, str[lex->sh->i]);
		lex->sh->i++;
	}
	lex->sh->i--;
	if (*name && **name)
		lex->sh->expand_len += get_expand_len(*name, lex->env, 0);
	lex->sh->j += (ft_strlen(get_env_value(lex->env, *name)) - 1);
	ft_strjustcat(lex->sh->tmp_str, get_env_value(lex->env, *name));
}
