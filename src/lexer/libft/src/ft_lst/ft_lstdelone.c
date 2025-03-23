/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:21:30 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/28 13:18:13 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Takes as a parameter a node and frees the memory of the node’s
 * content using the function ’del’ given as a parameter and free the node.
 * The memory of ’next’ must not be freed.
 * @param lst The node to free.
 * @param del The address of the function used to delete the content.
 * @return NONE
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->content);
	free(lst);
}
