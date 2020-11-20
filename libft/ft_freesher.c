/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freesher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:59:00 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 20:00:38 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freesher(char **str, int len)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}
