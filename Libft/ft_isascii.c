/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:00:08 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:10 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_isascii checks if the integer received belongs in the (ASCII)
 * table. If true it will return 1; if false return 0.
 * @param c 
 * @return int 
 */
int	ft_isascii(int c)
{
	unsigned char	asc;

	asc = (unsigned char)c;
	if (asc <= 127)
		return (1);
	else
		return (0);
}
