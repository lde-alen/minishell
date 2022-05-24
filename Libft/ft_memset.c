/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:10:42 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:26 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes len bytes of value c (converted to an unsigned char) to the
 * string b and returns it.
 * 
 * @param b 
 * @param c 
 * @param len 
 * @return void*
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)b;
	if (b == NULL)
		return (NULL);
	while (i < len)
		tmp[i++] = (unsigned char) c;
	b = tmp;
	return (b);
}
