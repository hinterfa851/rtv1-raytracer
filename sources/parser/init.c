/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:20:01 by glychest          #+#    #+#             */
/*   Updated: 2020/11/19 19:35:52 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		init(t_data *data)
{
	int w;
	int h;

	w = WIN_SIZE_X;
	h = WIN_SIZE_Y;
	if (!(data->mlx.mlx = mlx_init()))
		scene_error();
	if (!(data->mlx.win = mlx_new_window(data->mlx.mlx, w, h, "rtv1")))
		scene_error();
	if (!(data->img.img = mlx_new_image(data->mlx.mlx, w, h)))
		scene_error();
	if (!(data->img.img_data = mlx_get_data_addr(data->img.img,
			&data->img.bit_per_pixel, &data->img.size_line, &data->img.endline)))
		scene_error();
	if (!(data->canv.img = mlx_new_image(data->mlx.mlx, data->camera.canv_w,
			data->camera.canv_h)))
		scene_error();
	if (!(data->canv.img_data = mlx_get_data_addr(data->canv.img,
			&data->canv.bit_per_pixel, &data->canv.size_line, &data->canv.endline)))
		scene_error();
	return (0);
}

int		init_figur(t_data *data, char *type, char *line)
{
	t_obj	obj;
	t_obj	*new_obj;
	char	**tab;
	int		tab_len;
	int		t;

	tab = NULL;
	tab = ft_strsplit(line, ',');
	tab_len = len_tab(tab);
	t = find_type(type);
	if (tab_len < 10 || !t)
	{
		free_tab(tab);
		exit(error_output(PARAMETERS));
	}
	obj = init_object(new_vec(ft_atoi(tab[0]), ft_atoi(tab[1]),
	ft_atoi(tab[2])), new_vec(ft_strtodbl(tab[3]),
	ft_strtodbl(tab[4]), ft_strtodbl(tab[5])),
	ft_strtodbl(tab[6]), ft_strtodbl(tab[7]));
	obj = init_object_color(obj, ft_strtodbl(tab[8]), tab[9], t);
	new_obj = new_object(obj);
	ft_lstadd(&data->figur, ft_lstnew(new_obj, sizeof(t_obj)));
	free(new_obj);
	free_tab(tab);
	return (0);
}
