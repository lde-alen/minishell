/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitaz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:43:38 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/02 14:53:03 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/libft.h"

char	*ft_append(char *str, char c)
{
	char	*tmp;
	char	*src2;
	size_t	len_str;

	len_str = ft_strlen(str) + 2;
	tmp = (char *)malloc(sizeof(char) * len_str);
	src2 = (char *)malloc(sizeof(char) * 2);
	src2[0] = c;
	src2[1] = '\0';
	tmp = ft_strjoin(str, src2);
	free (src2);
	return (tmp);
}

ssize_t	sizeaz(char *str, char c)
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
			while (str[i] != '"')
				i++;
			i++;
		}
		if (str[i] == c)
			size++;
	}
	return (size);
}

char	**splitaz(char *str, char c)
{
	size_t	len;
	size_t	i;
	char	**tab;

	len = sizeaz(str, c);
	i = 0;
	ft_printf("The Initial Input is:\n%s\n", str);
	ft_printf("The number of rows are:\n%d\n", len);
	tab = (char **)malloc(sizeof(char) * len);
	if (!tab)
		return (NULL);
	while (len)
	{
		while (*str)
		{
			tab[i] = (char *)ft_calloc(1, sizeof(char));
			tab[i] = ft_append(tab[i], *str);
			str++;
		}
		i++;
		len--;
	}
	tab[i] = NULL;
	return (tab);
}

int	main(int ac, char **av)
{
	size_t	i;
	char	**tab;

	i = 0;
	tab = splitaz("echo \"test1 | test 2 | test 3\" | ls", '|');
	while (tab[i])
	{
		ft_printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
	return (1);
}
