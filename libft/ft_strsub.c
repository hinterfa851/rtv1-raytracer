/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:09:03 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 15:02:26 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char				*res;
	unsigned long int	i;

	if (s != NULL)
	{
		i = 0;
		if (!(res = malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			res[i] = s[start + i];
			i++;
		}
		res[len] = '\0';
		return (res);
	}
	return (NULL);
}
