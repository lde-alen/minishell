/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:00:02 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:40 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends string src to the end of dst. It will append at most
 * dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
 * dstsize is 0 or the original dst string was longer than dstsize (in practice
 * this should not happen as it means that either dstsize is incorrect or that
 * dst is not a proper string).
 * 
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*tmp_src;
	size_t	len_dest;
	size_t	len_src;
	size_t	total;
	size_t	i;

	tmp_src = (char *)src;
	len_src = ft_strlen(tmp_src);
	len_dest = ft_strlen(dst);
	total = 0;
	i = 0;
	if (dstsize > len_dest)
		total = len_src + len_dest;
	else
		total = len_src + dstsize;
	while (tmp_src[i] && (len_dest + 1) < dstsize)
	{
		dst[len_dest] = tmp_src[i];
		len_dest++;
		i++;
	}
	dst[len_dest] = '\0';
	return (total);
}
