/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:31:03 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 19:58:23 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Computes the length of the string and attempts
 * to compute the length of s, but never scans beyond the first maxlen bytes
 * of s. It returns the length of s.
 * 
 * @param str 
 * @return size_t 
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if ((char *)s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
