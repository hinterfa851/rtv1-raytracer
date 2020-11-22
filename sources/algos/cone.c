#include "../../includes/rtv1.h"

t_object	cr_cone(t_vec *p1, float radius, unsigned int color, t_vec *p4)
{
	t_vec *angletovec;
	t_vec *init_vec;
	t_object res;

	init_vec = cr_point(0, 1, 0);
	angletovec = malloc(sizeof(t_vec));
	res.p1 = p1;
	*angletovec = vec_rot(*init_vec, *p4);
	res.rot = angletovec;
	res.radius = radius;
	res.color = color;
	res.ray_intersect = &ray_intersect_cone;
	res.color_find = &color_find_cone;
	free(init_vec);
	free(p4);
	return (res);
}

float find_b_cone(t_vec *point, t_vec *p1, t_vec *rot, t_vec *dir)
{
	float res;
	t_vec *to_del;

	to_del = ft_substr(point, p1);
	res = 2 * (ft_scal(dir, to_del) - (1 + CON_ANG * CON_ANG) * ft_scal(dir, rot) * ft_scal(to_del, rot));
	free(to_del);
	return (res);
}

float find_c_cone(t_vec *point, t_vec *p1, t_vec *rot)
{
	float res;
	t_vec *to_del;

	to_del = ft_substr(point, p1);
	res = ft_scal(to_del, to_del) - (1 + CON_ANG * CON_ANG) * ft_scal(to_del, rot) * ft_scal(to_del, rot);
	free(to_del);
	return (res);
}

float	ray_intersect_cone(t_vec *dir, t_vec *point, t_object obj)
{
	float a;
	float b;
	float c;
	float d;
	float t;

	a = ft_scal(dir, dir) - (1 + CON_ANG * CON_ANG)
	* ft_scal(dir, obj.rot) * ft_scal(dir, obj.rot);
	b = find_b_cone(point, obj.p1, obj.rot, dir);
	c = find_c_cone(point, obj.p1, obj.rot);
	d = b * b - 4 * a * c;
	t = d < 0 ? -1 : get_t(a, b, d);	
	if (t < 0)
		return (0);
	return (t);
}

t_vec *find_cone_n(t_vec *point, t_scene *scene, t_vec *sender)
{
	t_vec *res;
	t_vec *a;
	t_vec *b;
	t_vec *n_cyl;

	a = ft_substr(point, (scene->objs[(int)sender->i].p1));
	n_cyl = find_n_cyl(sender->j, point, scene, sender->i);
	b = ft_substr(a, n_cyl);
	ft_vec_mult(b, (1 + CON_ANG * CON_ANG));
	res = ft_substr(a, b);
	free(a);
	free(b);
	free(n_cyl);
	return(res);
}

t_vec	*color_find_cone(t_vec *point, t_scene *scene, t_vec *sender, int k)
{
	t_vec *res;
	t_vec *vec1;
	t_vec *vec2;
	t_vec *n;
	t_vec *h;

	res = malloc(sizeof(t_vec));
	vec1 = ft_substr(point, scene->cam->pos);
	n = find_cone_n(point, scene, sender);
	vec2 = ft_substr(point, scene->light[k].pos);
	ft_normilize(n);
	ft_normilize(vec2);
	res->i = ft_scal(n, vec2);
	h = ft_add_vec(vec2, vec1);
	ft_normilize(h);
	res->j = ft_scal(h, n);
	free(vec1);
	free(vec2);
	free(n);
	free(h);
	return (res);
}
