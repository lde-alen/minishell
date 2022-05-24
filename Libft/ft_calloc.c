/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:32:45 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:07 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_calloc allocates enough space for count that size bytes and returns
 * a pointer to that allocated memory. 
 * @param count 
 * @param size 
 * @return void* 
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!(ptr))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
