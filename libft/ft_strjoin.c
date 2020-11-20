/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:29:22 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 00:16:16 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (s1 != NULL && s2 != NULL)
	{
		i = ft_strlen(s1);
		j = ft_strlen(s2);
		if (!(res = malloc(sizeof(char) * (i + j + 1))))
			return (NULL);
		ft_strcpy(res, s1);
		while (*res)
			res++;
		ft_strcpy(res, s2);
		return (res - i);
	}
	return (NULL);
}
