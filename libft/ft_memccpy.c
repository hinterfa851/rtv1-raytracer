/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 01:01:04 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/23 22:19:24 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long int	i;
	char				*s;
	char				*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	while (n > i++)
	{
		if ((*d++ = *s++) == (char)c)
			return (d);
	}
	return (NULL);
}
