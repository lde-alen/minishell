/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitaz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:43:38 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/09 19:47:14 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/libft.h"

static ssize_t	sizeaz(char *str, char c)
{
	ssize_t	i;
	size_t	size;

	i = -1;
	size = 1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
			i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			i++;
		}
		if (str[i] == c)
			size++;
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
		while (*s != c && *s && s)
		{
			if (*s == '"')
			{
				s++;
				len++;
				while (*s != '"')
				{
					s++;
					len++;
				}
				s++;
				len++;
			}
			if (*s == '\'')
			{
				s++;
				len++;
				while (*s != '\'')
				{
					s++;
					len++;
				}
				s++;
				len++;
			}
			len++;
			s++;
		}
		tab[i] = (char *)malloc(len + 1);
		if (!tab[i])
		{
			while (i)
				free(tab[--i]);
			free(tab);
			return (1);
		}
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

// int	main(void)
// {
// 	size_t	i;
// 	char	**tab;

// 	i = 0;
// 	tab = splitaz("echo \"karim |  amin | lucas\" | ls", '|');
// 	while (tab[i])
// 	{
// 		ft_printf("tab[%d] = %s\n", i, tab[i]);
// 		i++;
// 	}
// 	return (1);
// }
