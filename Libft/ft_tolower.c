/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:17:57 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:54 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a upper-case letter to the corresponding lower-case letter.
 * The argument must be representable as an unsigned char.
 * 
 * @param c 
 * @return int 
 */
int	ft_tolower(int c)
{
	unsigned int	asc;

	asc = (unsigned int)c;
	if (asc >= 'A' && asc <= 'Z')
		asc += 32;
	return (asc);
}
