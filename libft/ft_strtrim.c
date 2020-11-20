/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 21:59:45 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 19:52:56 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	int		i;
	int		len;
	int		j;

	if (!s)
		return (NULL);
	j = 0;
	len = (int)ft_strlen(s) - 1;
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (len >= i && len >= 0 &&
			(s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len--;
	if (!(new = (char *)malloc(sizeof(char) * (len - i + 2))))
		return (NULL);
	while (i <= len)
		new[j++] = s[i++];
	new[j] = '\0';
	return (new);
}
