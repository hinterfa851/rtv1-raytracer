/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:27:54 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/27 00:32:28 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	offset;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		offset = 0;
		while ((*haystack == *needle) && *needle)
		{
			haystack++;
			needle++;
			offset++;
		}
		if (!*needle)
			return (char *)(haystack - offset);
		else
		{
			haystack -= offset;
			needle -= offset;
		}
		haystack++;
	}
	return (NULL);
}
