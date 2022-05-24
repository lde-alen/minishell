/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:20:59 by lde-alen          #+#    #+#             */
/*   Updated: 2022/05/14 17:38:55 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_size(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && s++)
	{
		while (*s != c && *s)
			s++;
		count++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

/**
 * @brief fills tab
 * 
 * @param s 
 * @param c 
 * @param tab 
 * @return int 
 */
static int	fill_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s != c && *s && ++s)
			len++;
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
	tab[i] = 0;
	return (0);
}

/**
 * @brief Allocates (with malloc) and returns an array of strings obtained by
 * splitting ’s’ using the character ’c’ as a delimiter. The array must be ended
 * by a NULL pointer. Returns the array of new strings resulting from the split.
 * NULL if the allocation fails
 * 
 * @param s 
 * @param c 
 * @return char** (FREE REQ)
 */
char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	while (*s == c && *s)
		s++;
	tab = (char **)malloc(sizeof(char *) * (check_size(s, c) + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(s, c, tab))
		return (NULL);
	return (tab);
}
