/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:29:56 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 18:08:17 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstnew(void const *content, size_t content_size)
// {
// 	t_list *list;

// 	if (!(list = (t_list*)ft_memalloc(sizeof(t_list))))
// 		return (NULL);
// 	if (!content)
// 	{
// 		list->content = NULL;
// 		list->content_size = 0;
// 	}
// 	else
// 	{
// 		if ((list->content = ft_strdup(content)) == NULL)
// 			return (NULL);
// 		list->content_size = content_size;
// 	}
// 	list->next = NULL;
// 	return (list);
// }


t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *res;

	if ((res = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		if (!content)
		{
			res->content = NULL;
			res->content_size = 0;
		}
		else
		{
			if (!(res->content = ft_memalloc(content_size)))
			{
				free(res);
				return (NULL);
			}
			ft_memcpy(res->content, content, content_size);
			res->content_size = content_size;
		}
		res->next = NULL;
	}
	return (res);
}