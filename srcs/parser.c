/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/02 11:04:31 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ch_oper(char **rem)
// {
// 	int	i;

// 	i = 0;
// 	while (rem[i])
// 	{
// 		if ((strcmp(rem[i], "<") != 0 || strcmp(rem[i], "<<") != 0)
// 			|| (strcmp(rem[i], ">") != 0 || strcmp(rem[i], ">>") != 0)
// 			|| (strcmp(rem[i], "|") != 0 || strcmp(rem[i], "$") != 0))
// 		{
// 			ft_putstr_fd(BASH_SYN"syntax error near unexpected token\n", 2);
// 			break ;
// 		}
// 	}
// }

// void	ft_parser(char *str)
// {
// 	char	**rem;
// 	int i;

// 	i = 0;
// 	rem = ft_split(str, ' ');
// 	ch_oper(rem);
// }

void	ft_parse(char *str, t_env *lst)
{
	t_cmd	*cmd_lst;

	cmd_lst = ft_lst_init(str);
	exec_cmd(lst, cmd_lst);
}
