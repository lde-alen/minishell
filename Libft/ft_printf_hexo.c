/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:49:55 by lde-alen          #+#    #+#             */
/*   Updated: 2022/03/17 17:15:11 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hexo(va_list ap)
{
	unsigned int	hex;
	char			*base;
	unsigned int	count;

	hex = va_arg(ap, unsigned int);
	base = "0123456789ABCDEF";
	count = ft_strlen_hex(hex);
	ft_putnbr_un_base(hex, base);
	return (count);
}
