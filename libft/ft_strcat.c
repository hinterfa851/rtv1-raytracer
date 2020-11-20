/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 00:57:19 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/17 02:22:36 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *destptr, const char *srcptr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (*destptr)
	{
		destptr++;
		i++;
	}
	while (*srcptr)
	{
		*destptr = *srcptr;
		srcptr++;
		destptr++;
		j++;
	}
	*destptr = '\0';
	return (destptr - i - j);
}
