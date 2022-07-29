/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 23:08:16 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:59 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a pointer to the last occurrence of the character c in 
 * the string s.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char	*ft_strrchr(const char *s, int c)
{
	unsigned char	asc;
	size_t			len;
	char			*str;

	asc = (unsigned char)c;
	str = (char *) s;
	len = ft_strlen(str);
	if (str[len] == c)
		return ((char *)s + len);
	while (len--)
		if (str[len] == asc)
			return ((char *)s + len);
	return (NULL);
}
