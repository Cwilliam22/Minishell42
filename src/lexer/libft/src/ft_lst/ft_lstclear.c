/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:28:11 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/28 13:16:48 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes and frees the given node and every successor of that node,
 * using the function ’del’ and free(3). Finally, the pointer to the list must
 * be set to NULL.
 * @param lst The address of a pointer to a node.
 * @param del The address of the function used to delete the content of the
 * node.
 * @return NONE
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, *del);
		(*lst) = temp;
	}
}
