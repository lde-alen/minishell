/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:21:49 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:56 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc) and returns a substring from the string ’s’.
 * The substring begins at index ’start’ and is of maximum size ’len’.
 * Returns NULL if the allocation fails.
 * @param s 
 * @param start 
 * @param len 
 * @return char* (FREE REQ)
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen((char *)s);
	if (str_len - 1 < start)
		return (ft_strdup(""));
	str_len = ft_strlen((char *)&s[start]);
	if (str_len < len)
		str_len++;
	else
		str_len = len + 1;
	sub = (char *)ft_calloc(str_len, sizeof(char));
	if (sub)
		ft_strlcpy(sub, &s[start], str_len);
	return (sub);
}
