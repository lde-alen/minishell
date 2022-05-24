/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:21:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/05/14 22:30:42 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_ini2(size_t *i, size_t *j)
{
	*i = -1;
	*j = 0;
}

/**
 * @brief Combines all strings in the argument list and puts the result into
 * the returned string with dynamically allocated memory.
 * 
 * @param s1 
 * @param s2 
 * @return char* (FREE REQ)
 */
char	*ft_strjoin(char const *str, char const *buffer)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!str)
	{
		str = (char *)malloc(sizeof(char));
		str = "";
	}
	if (!str || !buffer)
		return (NULL);
	new = (char *)malloc(sizeof(char) * \
		(ft_strlen(str) + ft_strlen(buffer) + 1));
	if (!new)
		return (NULL);
	ft_ini2(&i, &j);
	if (str)
		while (str[++i] != '\0')
			new[i] = str[i];
	while (buffer[j] != '\0')
		new[i++] = buffer[j++];
	new[ft_strlen(str) + ft_strlen(buffer)] = '\0';
	free ((char *)str);
	return (new);
}
