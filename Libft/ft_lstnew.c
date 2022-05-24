/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:20:12 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:23 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Description Allocates (with malloc(3)) and returns a new element.
 * The variable ’content’ is initialized with the value of the parameter
 * ’content’. The variable ’next’ is initialized to NULL.
 * 
 * @param content 
 * @return t_list* 
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!(lst))
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
