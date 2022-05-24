/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:48:07 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:26 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies len bytes from string src to string dst.  The two strings may
 * overlap; the copy is always done in a non-destructive manner. Returns the
 * original value of dst and NULL if the conditions are invalid.
 * 
 * @param dst 
 * @param src 
 * @param len 
 * @return void* 
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmp_src;
	unsigned char		*tmp_dst;
	size_t				i;

	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	if (!tmp_dst || !tmp_src)
		return (NULL);
	if (tmp_src < tmp_dst)
	{
		while (len)
		{
			tmp_dst[len - 1] = tmp_src[len - 1];
			len--;
		}
	}
	i = 0;
	while (i < len)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dst);
}
