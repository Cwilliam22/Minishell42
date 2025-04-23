/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:04:17 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:50:53 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newobj;
	void	*newcontent;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		newobj = ft_lstnew(newcontent);
		if (!newobj)
		{
			del(newcontent);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newobj);
		lst = lst->next;
	}
	return (newlist);
}
