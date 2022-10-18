/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitaz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:43:38 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 20:10:44 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "../../includes/libft.h"

static ssize_t	sizeaz(char *str, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 1;
	while (i < ft_strlen(str))
	{
		if (str[i] == D_QUOTE)
			quote_loop(str, &i, D_QUOTE);
		else if (str[i] == S_QUOTE)
			quote_loop(str, &i, S_QUOTE);
		else
		{
			if (str[i] == c)
				size++;
			i++;
		}
	}
	return (size);
}

static int	fill_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s && s)
			splitaz_loop(&s, &len);
		tab[i] = (char *)malloc(len + 1);
		if (!tab[i])
			if (free_splitaz_tab(tab, &i))
				return (1);
		ft_strlcpy(tab[i++], s - len, len + 1);
		while (*s == c && *s)
			s++;
	}
	tab[i] = NULL;
	return (0);
}

char	**splitaz(char *str, char c)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (sizeaz(str, c) + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(str, c, tab))
		return (NULL);
	return (tab);
}
