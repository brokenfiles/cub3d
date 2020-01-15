/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:47:59 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:16:10 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;

	if (!(lst))
		return (NULL);
	if (!(new_list = ft_lstnew(f(lst->content))))
		return (NULL);
	current = new_list;
	while (lst)
	{
		if (lst->next)
		{
			if (!(new_list->next = ft_lstnew(f(lst->next->content))))
			{
				ft_lstclear(&current, del);
				return (NULL);
			}
			new_list = new_list->next;
		}
		lst = lst->next;
	}
	new_list->next = NULL;
	return (current);
}
