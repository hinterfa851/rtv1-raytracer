/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 01:38:57 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/26 21:48:32 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t			j;
	size_t			i;
	unsigned long	len;

	len = 0;
	j = ft_strlen(src);
	i = ft_strlen(dst);
	while (*dst)
		dst++;
	if (i > size)
		return (j + size);
	while (*src && ((len + i + 1) < size))
	{
		*dst = *src;
		src++;
		dst++;
		len++;
	}
	*dst = '\0';
	return (i + j);
}
