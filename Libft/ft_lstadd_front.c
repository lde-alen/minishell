/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:19:15 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:14 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief  Adds the element ’new’ at the beginning of the list.
 * 
 * @param alst 
 * @param new 
 */
void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	if (*alst)
	{
		new->next = *alst;
		*alst = new;
	}
	else
		*alst = new;
}
