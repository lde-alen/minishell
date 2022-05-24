/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:48:19 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:08 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_isalnum checks if the integer received is a character (ASCII)
 * and if that ASCII value is a digit or a letter. If true it will return 1;
 * if false return 0.
 * @param int
 * @return int
 */
int	ft_isalnum(int c)
{
	unsigned char	asc;

	asc = (unsigned char)c;
	if ((ft_isalpha(asc) == 1) || (ft_isdigit(asc) == 1))
		return (1);
	else
		return (0);
}
