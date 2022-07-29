/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:36:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/01/24 15:38:51 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_bzero writes n zeroed bytes to a string s.
 * 
 * @param s 
 * @param n 
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
