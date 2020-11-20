/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:19:16 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/27 15:14:10 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			res[j] = f(*s);
			s++;
			j++;
		}
		res[j] = '\0';
		return (res);
	}
	return (NULL);
}
