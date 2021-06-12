#include "../includes/rtv1.h"

int		init(d_mlx *data)
{
	int w;
	int h;

	w = WIN_SIZE_X;
	h = WIN_SIZE_Y;

//	data = malloc(sizeof(d_mlx)) ????

	if (!(data->connection_id = mlx_init()))
		scene_error();
	if (!(data->window_id = mlx_new_window(data->connection_id, w, h, "rtv1")))
		scene_error();
	if (!(data->image_id = mlx_new_image(data->connection_id, w, h)))
		scene_error();
	if (!(data->color_arr = mlx_get_data_addr(data->image_id,
			&data->bits_per_pixel, &data->size_line, &data->endian)))
		scene_error();

	// if (!(data->canv.img = mlx_new_image(data->mlx.mlx, data->camera.canv_w,
	// 		data->camera.canv_h)))
	// 	scene_error();
	// if (!(data->canv.img_data = mlx_get_data_addr(data->canv.img,
	// 		&data->canv.bit_per_pixel, &data->canv.size_line, &data->canv.endline)))
	// 	scene_error();

	return (0);
}

int		init_figur(scene *data, char *type, char *line, int object_index)
{
	object	*obj;
	object	*new_obj;
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
	obj = init_object(create_vector(ft_atoi(tab[0]), ft_atoi(tab[1]),
	ft_atoi(tab[2])), create_vector(ft_strtodbl(tab[3]),
	ft_strtodbl(tab[4]), ft_strtodbl(tab[5])),
	ft_strtodbl(tab[6]), ft_strtodbl(tab[7]));
	printf("init figur i, j, k - %f\t%f\t%f\n", obj->rotation->i, obj->rotation->j, obj->rotation->k);
	init_object_color(obj, ft_strtodbl(tab[8]), tab[9], t);
	
	//old
//	new_obj = new_object(obj);
//	ft_lstadd(&data->objects, ft_lstnew(new_obj, sizeof(object)));
	
	//new
	data->objects_array[object_index] = *obj;

//	free(new_obj);
	free_tab(tab);
	return (0);
}
