/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:11:12 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:25 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares byte string s1 against byte string s2.  Both strings are
 * assumed to be n bytes long. Returns zero if the two strings are identical,
 * otherwise returns the difference between the first two differing bytes
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while ((i < n - 1) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
