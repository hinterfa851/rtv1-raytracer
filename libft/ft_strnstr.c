/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 01:20:27 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/27 00:33:06 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		offset;
	size_t	n;

	n = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && (n < len))
	{
		offset = 0;
		while ((*haystack == *needle) && (n++ < len) && *needle)
		{
			haystack++;
			needle++;
			offset++;
		}
		if (!*needle)
			return (char *)(haystack - offset);
		else
		{
			haystack -= offset - 1;
			needle -= offset;
			n -= offset - 1;
		}
	}
	return (NULL);
}
