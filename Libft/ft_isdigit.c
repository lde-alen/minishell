/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:34:27 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:10 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_isdigit checks if the integer received is a character (ASCII)
 * and if that ASCII value is a digit. If true it will return 1; if false return 
 * 0.
 * @param c 
 * @return int 
 */
int	ft_isdigit(int c)
{
	unsigned char	asc;

	asc = (unsigned char)c;
	if (asc >= '0' && asc <= '9')
		return (1);
	else
		return (0);
}
