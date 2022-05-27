/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:20:17 by lde-alen          #+#    #+#             */
/*   Updated: 2022/05/27 10:13:43 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string needle
 * in the string haystack, where not more than len characters are searched.
 * Characters that appear after a `\0' character are not searched.
 * 
 * @param haystack 
 * @param needle 
 * @param len 
 * @return char* 
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;	

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] && needle[j] == haystack[i + j]
				&& (i + j) < len)
				j++;
			if (!needle[j])
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
