/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 00:36:58 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/27 15:14:43 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;
	int		j;

	if (s != NULL && f != NULL)
	{
		j = 0;
		i = ft_strlen(s);
		if (!(res = malloc((i + 1) * sizeof(char))))
			return (NULL);
		while (j < i)
		{
			res[j] = f(j, *s);
			s++;
			j++;
		}
		res[j] = '\0';
		return (res);
	}
	return (NULL);
}
