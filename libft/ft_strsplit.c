/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:40:10 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 19:57:10 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_end(char **str, int word)
{
	str[word] = NULL;
	return (str);
}

static char		**ft_writer(char **str, char const *s, char c, int i)
{
	int end;
	int word;
	int start;

	word = 0;
	start = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i--;
		end = 0;
		while (s[++i] && s[i] != c)
			end++;
		if (end > 0)
		{
			if (!(str[word++] = (char *)malloc(sizeof(char) * (end + 1))))
				return (ft_freesher(str, word));
			end = 0;
			while (s[start] != c && s[start])
				str[word - 1][end++] = s[start++];
			str[word - 1][end] = '\0';
		}
	}
	return (ft_end(str, word));
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		word;

	if (!s)
		return (NULL);
	word = ft_wordcount(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	return (ft_writer(str, s, c, 0));
}
