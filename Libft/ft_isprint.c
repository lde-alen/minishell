/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:10:02 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:11 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_isprint checks if the integer received is a character (ASCII)
 * and if that ASCII value is part of the printable characters in the ASCII
 * table. If true it will return 1; if false return 0.
 * @param c 
 * @return int 
 */
int	ft_isprint(int c)
{
	unsigned char	asc;

	asc = (unsigned char)c;
	if (asc >= ' ' && asc <= '~')
		return (1);
	else
		return (0);
}
