/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:21 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/11 08:26:33 by lde-alen         ###   ########.fr       */
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

size_t	ft_fill_first_arg(t_msh *msh, size_t i, char *tmp)
{
	while (msh->cmd->command[i] && msh->cmd->command[i] != ' '
		&& msh->cmd->command[i] != '<' && msh->cmd->command[i] != '>'
		&& msh->cmd->command[i] != '|')
	{
		ft_append_back(&tmp, msh->cmd->command[i]);
		i++;
	}
	return (i);
}

/**
 * should be fine
 */
char	*ft_args_to_str(t_msh *msh)
{
	size_t	i;
	char	*tmp;

	tmp = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (msh->cmd->command[i])
	{
		while (msh->cmd->command[i] == ' ')
			i++;
		if (msh->cmd->command[i] == '<' || msh->cmd->command[i] == '>')
		{
			i++;
			if (msh->cmd->command[i] == '<' || msh->cmd->command[i] == '>')
				i++;
			while (msh->cmd->command[i] == ' ')
				i++;
			while (msh->cmd->command[i] != ' ' && msh->cmd->command[i] != '>'
				&& msh->cmd->command[i] != '<' && msh->cmd->command[i] != '|')
					i++;
				i++;
		}
		while (msh->cmd->command[i] == ' ')
			i++;
		tmp = ft_strjoin(tmp, " ");
		while (msh->cmd->command[i] != ' ' && msh->cmd->command[i] != '>'
			&& msh->cmd->command[i] != '<' && msh->cmd->command[i] != '|'
			&& msh->cmd->command[i])
		{
			ft_append_back(&tmp, msh->cmd->command[i]);
			i++;
		}
		i++;
	}
	return (tmp);
}

size_t	ft_count_args(char *args)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (args[i])
	{
		while (args[i] == ' ')
			i++;
		if (args[i] != ' ')
		{
			count++;
			while (args[i] && args[i] != ' ')
				i++;
		}
		i++;
	}
	return (count);
}

void	ft_fill_arg(t_msh *msh)
{
	size_t	i;
	size_t	nb_args;
	char	*args;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(1, sizeof(char));
	i = ft_fill_first_arg(msh, i, tmp);
	args = ft_args_to_str(msh);
	nb_args = ft_count_args(args);
	msh->cmd->argument = (char **)malloc(sizeof(char *) * (nb_args + 1));
	msh->cmd ->argument = ft_split(args, ' ');
	free(msh->cmd->command);
	msh->cmd->command = msh->cmd ->argument[0];
	ft_print_char_arr(msh->cmd->argument);
	ft_printf("initial string before split is: %s\n", args);
	ft_printf("the nb of args is: %d\n", nb_args);
	ft_printf("the value of i is: %d\n", i);
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
