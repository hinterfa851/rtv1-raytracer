/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 23:13:45 by glychest          #+#    #+#             */
/*   Updated: 2020/11/19 19:37:05 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		camera(t_data *p, char **tab)
{
	char	**str;

	str = NULL;
	str = ft_strsplit(tab[1], ',');
	if (len_tab(str) < 6)
	{
		free_tab(str);
		error_output(PARAMETERS);
		exit(-1);
	}
	p->camera.canv_h = ft_atoi(str[0]);
	p->camera.canv_w = ft_atoi(str[1]);
	p->camera.canv_d = ft_atoi(str[2]);
	p->camera.x = ft_strtodbl(str[3]);
	p->camera.y = ft_strtodbl(str[4]);
	p->camera.z = ft_strtodbl(str[5]);
	free_tab(str);
	return (0);
}

void	ambience(t_data *p, char *s)
{
	p->ambient = ft_strtodbl(s);
	// if (p->ambient > 1)
	// 	p->ambient = 1;
}

t_vector	new_vec(double x, double y, double z)
{
	t_vector vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
