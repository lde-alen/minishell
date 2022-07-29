/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_u.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:50:17 by lde-alen          #+#    #+#             */
/*   Updated: 2022/03/17 17:15:33 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_putnbr_u(va_list ap)
{
	unsigned long int	nb;

	nb = va_arg(ap, unsigned int);
	return (ft_putnbr(nb));
}
