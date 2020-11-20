/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:47:56 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 18:19:39 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *temp;
	t_list *new;
	t_list *lst_0;

	if (!lst || !f)
		return (NULL);
	lst_0 = lst;
	temp = f(lst_0);
	new = temp;
	while (lst_0->next)
	{
		temp->next = f(lst_0->next);
		lst_0 = lst_0->next;
		temp = temp->next;
	}
	return (new);
}
