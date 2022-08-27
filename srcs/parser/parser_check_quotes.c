/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:05 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/27 23:12:34 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_fill_quotes(char *str, char quote, t_sh *sh, t_env *env)
// {
// 	if (str[sh->i] == '\'' || str[sh->i] == '"')
// 	{
// 		if (str[sh->i] == '\'')
// 			sh->sq += 1;
// 		if (str[sh->i] == '"')
// 			sh->dq += 1;
// 		if ((quote == '\'' && sh->dq == 0) || (quote == '"' && sh->sq == 0))
// 		{
// 			sh->i++;
// 			if (str[sh->i] && ft_strchr((str + sh->i), quote) != NULL)
// 			{
// 				while (str[sh->i] != quote && str[sh->i])
// 				{
// 					if (str[sh->i] == '$' && quote == '"')
// 						ft_expand(env, "$PATH");
// 					sh->i++;
// 				}
// 			}
// 		}
// 	}
// 	return (0);
// }

int	check_quotes(char *str, char quote, t_msh *msh)
{
	if (str[msh->sh->i] == '\'' || str[msh->sh->i] == '"')
	{
		if (str[msh->sh->i] == '\'')
			msh->sh->sq += 1;
		if (str[msh->sh->i] == '"')
			msh->sh->dq += 1;
		if ((quote == '\'' && msh->sh->dq == 0) ||
			(quote == '"' && msh->sh->sq == 0))
		{
			msh->sh->i++;
			if (str[msh->sh->i] == '$' && quote == '"')
				ft_check_expand(str, msh);
			if (str[msh->sh->i] && ft_strchr((str + msh->sh->i), quote) != NULL)
			{
				while (str[msh->sh->i] != quote && str[msh->sh->i])
					msh->sh->i++;
			}
			else
			{
				if (quote == '\'')
					ft_putstr_fd("Error: Missing quote... RTFPDF.\n", 2);
				if (quote == '"')
					ft_putstr_fd("Error: missing dquote... RTFPDF\n", 2);
				return (1);
			}
		}
	}
	return (0);
}
