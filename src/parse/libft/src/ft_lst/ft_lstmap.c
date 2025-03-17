/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:45:42 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/28 13:22:54 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list ’lst’ and applies the function ’f’ on the content
 * of each node. Creates a new list resulting of the successive applications
 * of the function ’f’. The ’del’ function is used to delete the content of
 * a node if needed.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content of a node if
	needed.
 * @return The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new_map;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_map = NULL;
	while (lst)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (!temp)
		{
			del(content);
			ft_lstclear(&new_map, del);
			return (NULL);
		}
		ft_lstadd_back(&new_map, temp);
		lst = lst->next;
	}
	temp->next = NULL;
	return (new_map);
}
