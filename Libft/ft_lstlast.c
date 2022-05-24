/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:19:55 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:19 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the last element of the list.
 * 
 * @param last 
 * @return t_list* 
 */
t_list	*ft_lstlast(t_list *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}
