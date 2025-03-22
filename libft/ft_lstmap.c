/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:04:05 by davihako          #+#    #+#             */
/*   Updated: 2025/01/13 20:04:05 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*core;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	core = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&core, del);
			return (NULL);
		}
		if (!core)
			core = new_node;
		else
			(ft_lstlast(core))->next = new_node;
		lst = lst->next;
	}
	return (core);
}
