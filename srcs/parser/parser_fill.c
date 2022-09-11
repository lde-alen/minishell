/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:21 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/11 04:48:32 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * count how many args
 * malloc first array
 * fill array [0] - done
 * finish filling the rest
 * parse the rest
 */
void	ft_fill_arg(t_msh *msh)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(1, sizeof(char));
	while (msh->cmd->command[i] && msh->cmd->command[i] != ' ' && msh->cmd->command[i] != '<' && msh->cmd->command[i] != '>' && msh->cmd->command[i] != '|')
	{
		ft_append_back(&tmp, msh->cmd->command[i]);
		i++;
	}
	ft_printf("the value of tmp is: %s\n", tmp);
}

void	ft_init_file(char **file, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		file[i] = (char *)malloc(sizeof(char));
		file[i] = "";
		i++;
	}
	file[i] = NULL;
}

void	ft_fill_command(char **tab, size_t i, t_msh *msh)
{
	size_t	j;

	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		msh->cmd->command = ft_strdup(tab[i] + j);
		msh->cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
		// ft_printf("%s\n", msh->cmd->command);
		i++;
	}
}
