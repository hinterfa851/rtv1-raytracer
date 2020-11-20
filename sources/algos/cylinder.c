#include "../../includes/rtv1.h"

t_object	cr_cylinder(t_vec *p1, float radius, unsigned int color, t_vec *p4)	// angle_to_vec
{
	t_object res;
	t_vec *angletovec;
	t_vec *init_vec;

	init_vec = cr_point(0, 1, 0);
	angletovec = malloc(sizeof(t_vec));
	res.p1 = p1;
	*angletovec = vec_rot(*init_vec, *p4);
	res.rot = angletovec;
	res.radius = radius;
	res.color = color;
	res.ray_intersect = ray_intersect_cylinder;
	res.color_find = color_find_cylinder;
	free(init_vec);
	return (res);
}

float	ray_intersect_cylinder(t_vec *dir, t_vec *point, t_object obj)		// DANGER
{
	float a;
	float b;
	float c;
	float d;
	float t;

	a = ft_scal(dir, dir) - ft_scal(dir, obj.rot)
	* ft_scal(dir, obj.rot);
	b = 2 * (ft_scal(dir, ft_substr(point, obj.p1)) - ft_scal(dir, obj.rot)
	* ft_scal(ft_substr(point, obj.p1), obj.rot));
	c = ft_scal(ft_substr(point, obj.p1), ft_substr(point, obj.p1))
	- ft_scal(ft_substr(point, obj.p1), obj.rot)
	* ft_scal(ft_substr(point, obj.p1), obj.rot) - obj.radius * obj.radius;
	d = b * b - 4 * a * c;
	t = d < 0 ? -1 : get_t(a, b, d);
	if (t < 0)
		return (0);
	return (t);
}

t_vec	*find_n_cyl(float t, t_vec *point, t_scene *scene, int index)		// t_vec *res
{
	t_vec *res;
	t_vec *obj;
	t_vec *va;
	t_vec *po;
	float k;

	obj = (scene->objs[index].p1);
	va = scene->objs[index].rot;
	k = (ft_scal(va, point) - ft_scal(va, obj)) / (ft_scal(va, va));
	po = cr_point(obj->i + k * va->i, obj->j + k * va->j, obj->k + k * va->k);
	res = ft_substr(po, point);
	free(po);
	t += 0;
	return (res);
}

t_vec	*color_find_cylinder(t_vec *point, t_scene *scene, t_vec *sender, int k)	// t_vec *res
{
	t_vec *n;
	t_vec *res;
	t_vec *vec1;
	t_vec *vec2;
	t_vec *h;
	
	res = malloc(sizeof(t_vec));
	vec2 = ft_substr(point, scene->light[k].pos);
	vec1 = ft_substr(point, scene->cam->pos);
	n = find_n_cyl(sender->j, point, scene, sender->i);
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
