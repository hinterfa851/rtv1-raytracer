/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:41:34 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/19 20:49:16 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned long i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (*s1 && *s2)
	{
		while ((*s1 == *s2) && (i < n) && *s1)
		{
			s1++;
			s2++;
			i++;
		}
	}
	if ((*s1 == '\0' && *s2 == '\0') || i == n)
		return (1);
	return (0);
}
