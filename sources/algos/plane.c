#include "../../includes/rtv1.h"

t_object	cr_plane(t_vec *p1, t_vec *rot, unsigned int color)	// t_vec *angletovec
{
	t_vec *angletovec;
	t_object res;
	t_vec *init_vec;

	init_vec = cr_point(0, 0, 1);
	angletovec = malloc(sizeof(t_vec));
	*angletovec = vec_rot(*init_vec, *rot);
	res.p1 = p1;
	res.rot = angletovec;
	res.color = color;
	res.ray_intersect = ray_intersect_pl;
	res.color_find = color_find_pl;
	free(init_vec);
	return (res);
}

float	ray_intersect_pl(t_vec *dir, t_vec *point, t_object object)		// clear
{
	float res;
	t_vec *x;

	x = ft_substr(point, object.p1);
	res = -1 * ft_scal(x, object.rot) / ft_scal(dir, object.rot);
	if (res < 0)
		return (0);
	free(x);
	return (res);
}

// float	find_vec(t_vec *light, t_vec *cam, t_vec normal)			// usless??
// {
// 	t_vec *b;
// 	float res;

// 	ft_normilize(&normal);
// 	b = ft_substr(cam, ft_vec_mult(&normal, 2 * ft_scal(cam, &normal)));
// 	res = find_cos(b, light);
// 	free(b);
// 	return (res);
// }

t_vec *color_find_pl(t_vec *point, t_scene *scene, t_vec *sender, int k)	// t_vec *res 
{
	t_vec *h;
	t_vec *vec2;
	t_vec *res;
	t_vec *vec1;
	t_vec *test;

	res = malloc(sizeof(t_vec *));
	vec2 = ft_substr(point, scene->light[(int)sender->k].pos);
	vec1 = ft_substr(scene->cam->pos, point);
//	test2 = vec_rot(*cr_point(1, 0, 0), *(scene->objs[index].rot));
	// test = scene->objs[index].rot;
	// cc = find_vec(vec2, vec1, *test);
	test = scene->objs[(int)sender->i].rot;
	vec2 = ft_substr(point, scene->light[(int)sender->k].pos);
	ft_normilize(test);
	ft_normilize(vec2);
	res->i = ft_scal(test, vec2);
	h = ft_add_vec(vec2, vec1);
	ft_normilize(h);
	res->j = ft_scal(h, test);
	free(vec1);
	free(vec2);
	free(h);
	k += 0;
	return (res);
}
