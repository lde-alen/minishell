/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:02:18 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/07 00:08:51 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a pointer to the first occurrence of the character c in 
 * the string s.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char	*ft_strchr(const char *s, int c)
{
	unsigned char	asc;
	unsigned int	i;
	char			*str;

	asc = (unsigned char)c;
	i = 0;
	if (!s)
		return (NULL);
	str = (char *) s;
	while (str[i] && str[i] != asc)
		i++;
	if (str[i] == asc)
		return ((char *)s + i);
	return (NULL);
}
