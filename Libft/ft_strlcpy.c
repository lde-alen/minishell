/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:54:11 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:43 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy and concatenate strings with the same input parameters and 
 * output the result. It takes the full size of the destination buffer and 
 * guarantee NUL-termination if there is room.
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen((char *)src);
	if (dstsize != 0)
	{
		if (len >= dstsize)
		{
			ft_memcpy(dst, src, dstsize - 1);
			dst[dstsize - 1] = '\0';
		}
		else
			ft_memcpy(dst, src, len + 1);
	}
	return (len);
}
