/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:34:22 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 23:40:37 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a pointer to a new string which is a duplicate of the
 * string s.  Memory for the new string is obtained with malloc, and can be
 * freed with free.
 * 
 * @param s1 
 * @return char* (FREE REQ)
 */
char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*str;
	char	*tmp;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen((char *)s1);
	tmp = (char *)malloc((sizeof(char) * (len + 1)));
	str = (char *)s1;
	if (!tmp)
		return (NULL);
	while (str[len])
		len++;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
