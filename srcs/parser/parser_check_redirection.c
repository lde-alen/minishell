/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/16 14:46:17 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
int	check_redirections(char *str, t_lex *lex)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			while (str[i] && str[i] == ' ')
				i++;
		if (str[i] == '"')
			redir_d_quote_check(lex, str, &i);
		else if (str[i] == '\'')
			redir_s_quote_check(lex, str, &i);
		else if (str[i] == '>')
		{
			i++;
			if (redir_r_redir(lex, str, &i))
				return (1);
			i--;
		}
		else if (str[i] == '<')
			if (redir_l_redir(lex, str, &i))
				return (1);
		i++;
	}
	return (0);
}
