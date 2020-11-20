/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:20:19 by glychest          #+#    #+#             */
/*   Updated: 2020/11/20 16:15:11 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void fill_z_buffer(t_scene *scene)
{
    int i;

    i = 0;
    scene->z_buffer = malloc(WIDTH * HEIGHT * sizeof(float));
    while(i < WIDTH * HEIGHT)
        scene->z_buffer[i++] = MAXDISTANCE;
}

void memorer(t_scene *scene, t_mx *box)
{
	if (!(box = malloc(sizeof(t_mx))))
        error_handler("memory error");
 	if (!(scene = malloc(sizeof(t_scene))))
        error_handler("memory error");
    if (!(scene->cam = malloc(sizeof(t_cam))))
        error_handler("memory error");
}

t_object cr_object(t_obj *data)
{
	t_vec *pos;
	t_vec *rot;

	pos = cr_point(data->c.x, data->c.y, data->c.z);
	rot = cr_point(data->v.x, data->v.x, data->v.x);
	if (data->type == 1)
		return (cr_sphere(pos, data->r, data->color, rot));
	else if (data->type == 2)
        return (cr_cylinder(pos, data->r, data->color, rot));
	else if (data->type == 3)
        return (cr_cone(pos, data->r, data->color, rot));
    return (cr_plane(pos, rot, data->color));
}

int count_light_len(t_list *light)
{
	int res;

	res = 0;
	while (light)
	{
		light = light->next;
		res++;
	}
	return (res);
}

void fill_middleware(t_scene *scene, t_data data, t_mx *box)
{
	int i;
	int j;

	i = 0;
	j = 0;
//	memorer(scene, box);
	// printf("*Ok\t %d\n", data.obj_n);
	scene->obj_count = data.obj_n;
	// printf("Ok\n");
	fill_z_buffer(scene);
	scene->objs = malloc(sizeof(t_object) * scene->obj_count);
	while(i < data.obj_n)
	{
		// printf("%d\n", i);
		scene->objs[i] = cr_object((t_obj *)data.figur->content);
		data.figur = data.figur->next;
		i++;
	}
	scene->cam->dir	 = cr_point(data.camera.x, data.camera.y, data.camera.z);
	scene->cam->pos = cr_point(data.camera.canv_h, data.camera.canv_w, data.camera.canv_d);
	i = count_light_len(data.light);
	scene->light = malloc(sizeof(t_light) * i);
	scene->light_count = i;
	// printf("hui\n");
	// printf("\n%d\n", i);
	// printf("\n%f\t%f\t%f\n", ((t_light *)(data.light->content))->x, ((t_light *)(data.light->content))->y, ((t_light *)(data.light->content))->z);
	while(j < i)
	{
		// printf("saving\n");
		// printf("test - %f\t%f\t%f\n", (((t_light *)(data.light)->content))->x, (((t_light *)(data.light)->content))->y, (((t_light *)(data.light)->content))->z);
		scene->light[j].pos = cr_point(((t_light *)(data.light->content))->x, ((t_light *)(data.light->content))->y, ((t_light *)(data.light->content))->z);
		scene->light[j].power = ((t_light *)(data.light->content))->intens;
		data.light = data.light->next;
		j++;
	}
	box->conn_id = data.mlx.mlx;
	box->win_id = data.mlx.win;
	box->image_id = data.img.img;
	box->draw_arr = data.img.img_data;
	box->bits_per_pixel = data.canv.bit_per_pixel;
	box->size_line = data.canv.size_line;
	box->endian = data.canv.endline;
}

int		main(int argc, char **argv)
{
	t_data	data;
	t_scene *scene;
	t_mx *box;

	if (argc == 2)
	{
		if ((read_file(&data, argv[1])) == -1)
			return (0);
		// render + draw
		printf("ok\n");
		if (!(box = malloc(sizeof(t_mx))))
      	  error_handler("memory error");
 		if (!(scene = malloc(sizeof(t_scene))))
        	error_handler("memory error");
    	if (!(scene->cam = malloc(sizeof(t_cam))))
        	error_handler("memory error");
		fill_middleware(scene, data, box);
		printf("in main %f\t%f\t%f\n", scene->light[0].pos->i, scene->light[0].pos->j, scene->light[0].pos->k);
		printf("in main %f\t%f\t%f\n", scene->objs[0].p1->i, scene->objs[0].p1->j, scene->objs[0].p1->k);
		printf("in main %f\t%f\t%f\n", scene->cam->pos->i, scene->cam->pos->j, scene->cam->pos->k);
	//	printf("%f\t%f\t%f\n", ((t_light *)(data.light->content))->x, ((t_light *)(data.light->content))->y, ((t_light *)(data.light->content))->z);
		// printf("%f\t%f\t%f\n", scene->objs[0].p1->i, scene->objs[0].p1->j, scene->objs[0].p1->k);
		// printf("%f\t%f\t%f\n", scene->light[0].pos->i, scene->light[0].pos->j, scene->light[0].pos->k);
		// mlx_put_image_to_window(data.mlx.mlx, data.mlx.win, data.img.img, 0, 0);
		// mlx_hook(data.mlx.win, 2, 0, key_press, &data);
		// mlx_hook(data.mlx.win, 17, 1L << 17, escape, &data);
		// mlx_loop(data.mlx.mlx);
		// box->conn_id = mlx_init();
    	// box->win_id = mlx_new_window(box->conn_id, WIDTH, HEIGHT, "RTv1");
    	// box->image_id = mlx_new_image(box->conn_id, WIDTH, HEIGHT);
    	// box->draw_arr = mlx_get_data_addr(box->image_id, &(box->bits_per_pixel), &(box->size_line), &(box->endian));
    	render(scene,  box);
		mlx_put_image_to_window(box->conn_id, box->win_id, box->image_id, 0, 0);
		mlx_loop(box->conn_id);
	}
	else
		error_output(USAGE);
	return (0);
}
