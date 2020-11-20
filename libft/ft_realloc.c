/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:50:44 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 17:51:32 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *old, size_t new_len)
{
	size_t	old_len;
	void	*new;

	if (!(old))
		return (NULL);
	old_len = ft_strlen(old);
	if (!(new = ft_memalloc(new_len + 1)))
	{
		free(old);
		return (NULL);
	}
	ft_bzero(new, new_len);
	ft_memcpy(new, old, new_len);
	free(old);
	return (new);
}
