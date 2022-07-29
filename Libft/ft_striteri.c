/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:21:10 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:34 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function f to each character of the string passed as
 * argument, and passing its index as first argument. Each character is passed
 * by address to f to be modified if necessary
 * 
 * @param s 
 * @param f 
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
