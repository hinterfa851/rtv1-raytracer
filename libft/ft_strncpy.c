/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 01:52:32 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/19 22:28:37 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned long i;

	i = 0;
	while (*src && (i < len))
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	while (i < len)
	{
		*dst = '\0';
		dst++;
		i++;
	}
	return (dst - len);
}
