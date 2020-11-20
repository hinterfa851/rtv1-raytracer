/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:17:49 by hinterfa          #+#    #+#             */
/*   Updated: 2019/09/28 20:31:16 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int res;

	res = 0;
	if (n < 0)
	{
		res++;
		n *= -1;
	}
	while (n / 10 != 0)
	{
		res++;
		n /= 10;
	}
	return (++res);
}

static void	filler(char *str, int n)
{
	if (n / 10 != 0)
	{
		*str = '0' + n % 10;
		str++;
		filler(str, n / 10);
	}
	else
	{
		*str = '0' + n % 10;
		str++;
	}
}

static int	check(int n, char *res, char *rres, int i)
{
	int j;

	if (n < 0)
	{
		*rres = '-';
		*res = '-';
		res++;
		rres++;
		n *= -1;
		i--;
	}
	filler(res, n);
	res += i;
	*res = '\0';
	res--;
	j = 0;
	while (j++ < i)
	{
		*rres = *res;
		rres++;
		res--;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*res;
	char	*rres;
	int		i;

	i = int_len(n);
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (!(rres = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n == -2147483648)
		return (ft_strcat(ft_itoa(-21474), ft_itoa(83648)));
	i = check(n, res, rres, i);
	i = (res[0] == '-') ? i + 1 : i;
	rres[i] = '\0';
	return (rres);
}
