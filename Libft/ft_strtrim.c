/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:21:39 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:57 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a copy of ’s1’ with the
 * characters specified in ’set’ removed from the beginning and the end of
 * the string. Return NULL if the allocation fails.
 * 
 * @param s1 
 * @param set 
 * @return char* (FREE REQ)
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	len;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen((char *)s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	return (res);
}
