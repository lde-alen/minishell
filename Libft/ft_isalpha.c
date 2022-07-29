/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:20:11 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:09 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_isalpha checks if the integer received is a character (ASCII)
 * and if that ASCII value is a letter. If true it will return 1; if false 
 * return 0.
 * @param c 
 * @return int
 */
int	ft_isalpha(int c)
{
	unsigned char	asc;

	asc = (unsigned char)c;
	if ((asc >= 'A' && asc <= 'Z') || (asc >= 'a' && asc <= 'z'))
		return (1);
	else
		return (0);
}
