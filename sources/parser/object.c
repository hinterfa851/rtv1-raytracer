/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 23:51:04 by glychest          #+#    #+#             */
/*   Updated: 2020/11/19 19:36:25 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

t_obj	*new_object(t_obj new)
{
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->c = new.c;
	obj->v = new.v;
	obj->a = new.a;
	obj->r = new.r;
	obj->specular = new.specular;
	obj->color = new.color;
	obj->type = new.type;
	return (obj);
}


t_obj	init_object_color(t_obj obj, double specular, char *color, int type)
{
	obj.specular = specular;
	if (ft_strequ(color, "red"))
		obj.color = RED;
	else if (ft_strequ(color, "green"))
		obj.color = GREEN;
	else if (ft_strequ(color, "blue"))
		obj.color = BLUE;
	else
		obj.color = 249710846;
	obj.type = type;
	return (obj);
}

t_obj	init_object(t_vector c, t_vector v, double a, double r)
{
	t_obj	obj;

	obj.c = c;
	obj.v = v;
	while (a > 360.0)
		a -= 360.0;
	while (a < 0.0)
		a += 360.0;
	obj.a = (a * PI) / 180.0;
	obj.r = r;
	return (obj);
}

int		create_object(t_data *data, char *line)
{
	char	**tab;
	int		ret;

	tab = NULL;
	ret = 0;
	tab = ft_strsplit(line, ' ');
	if (ft_strequ(tab[0], "sphere") || ft_strequ(tab[0], "cylinder") ||
	ft_strequ(tab[0], "cone") || ft_strequ(tab[0], "plane"))
	{
		ret = init_figur(data, tab[0], tab[1]);
		if (ret == -1)
			return (-1);
	}
	if (ft_strequ(tab[0], "camera"))
	{
		data->camera.cam++;
		if ((camera(data, tab)) == -1)
			exit(0);
	}
	if (ft_strequ(tab[0], "light"))
		set_light(data, tab);
	// if (ft_strequ(tab[0], "ambient"))
	// 	ambience(data, tab[1]);
	free_tab(tab);
	return (0);
}


int		count_object(char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_output(NO_FD));
	while ((get_next_line(fd, &line)) > 0)
	{
		if ((ft_strncmp(line, "sphere", 6)) == 0 ||
		(ft_strncmp(line, "cylinder", 8)) == 0 ||
		(ft_strncmp(line, "cone", 4)) == 0 ||
		(ft_strncmp(line, "plane", 5)) == 0)
			i++;
		free(line);
	}
	close(fd);
	return (i);
}
