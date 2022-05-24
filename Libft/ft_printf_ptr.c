/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:50:03 by lde-alen          #+#    #+#             */
/*   Updated: 2022/03/17 17:15:18 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_ptr(va_list ap)
{
	int						i;
	unsigned long long int	nb;
	static char				*ptr;
	int						hex;

	hex = 0;
	nb = va_arg(ap, unsigned long long int);
	i = ft_strlen_hex(nb);
	ptr = ft_calloc(sizeof(char), (i + 1));
	if (nb == 0)
		ptr[i - 1] = '0';
	ft_asc_to_hex(ptr, i - 1, nb, hex);
	if (hex == 0)
	{
		if (ptr[i - 1] == '0' && (i - 1) == 0)
			ft_printf("%s", "0x0");
		else
			ft_printf("0x%s", ptr);
	}
	else
		ft_printf("%s", ptr);
	free(ptr);
	ptr = NULL;
	return (i + 2);
}
