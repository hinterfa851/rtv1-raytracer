/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 01:35:45 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/27 00:07:22 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *destptr, const char *srcptr, size_t num)
{
	unsigned long int	j;
	int					i;

	j = 0;
	i = 0;
	while (*destptr)
	{
		destptr++;
		i++;
	}
	while (j < num && *srcptr != '\0')
	{
		*destptr = *srcptr;
		srcptr++;
		j++;
		destptr++;
	}
	if (j <= num)
	{
		*destptr = '\0';
		j++;
		destptr++;
	}
	return (destptr - i - j);
}
