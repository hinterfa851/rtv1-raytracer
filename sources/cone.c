#include "../includes/rtv1.h"

float find_b_cone(vector *point, vector *p1, vector *rot, vector *dir)
{
	float res;
	vector *to_del;

	to_del = substr_vector(point, p1);
	res = 2 * (ft_scal(dir, to_del) - (1 + CON_ANG * CON_ANG) * ft_scal(dir, rot) * ft_scal(to_del, rot));
	free(to_del);
	return (res);
}

float find_c_cone(vector *point, vector *p1, vector *rot)
{
	float res;
	vector *to_del;

	to_del = substr_vector(point, p1);
	res = ft_scal(to_del, to_del) - (1 + CON_ANG * CON_ANG) * ft_scal(to_del, rot) * ft_scal(to_del, rot);
	free(to_del);
	return (res);
}

float	ray_intersect_cone(vector *dir, vector *point, object *obj)
{
	float a;
	float b;
	float c;
	float d;
	float t;

	a = ft_scal(dir, dir) - (1 + CON_ANG * CON_ANG)
	* ft_scal(dir, obj->rotation) * ft_scal(dir, obj->rotation);
	b = find_b_cone(point, obj->position, obj->rotation, dir);
	c = find_c_cone(point, obj->position, obj->rotation);
	d = b * b - 4 * a * c;
	t = d < 0 ? -1 : get_t(a, b, d);	
	if (t < 0)
		return (0);
	return (t);
}

void find_normal_cone(vector *intersection_point, object *figure, vector *result_normal)
{
	vector to_point;
	vector cylinder_normal;
	vector diff;
	vector multiplied;

	vector axis_point;
	vector vec;
	float koef;

	substr_vector_by_pointer(intersection_point, figure->position, &to_point);
	find_normal_cylinder(intersection_point, figure, &cylinder_normal);
	substr_vector_by_pointer(&to_point, &cylinder_normal, &diff);
	vector_float_multiply(&diff, (1 + CON_ANG * CON_ANG), &multiplied);
	substr_vector_by_pointer(&to_point, &multiplied, result_normal);
	ft_normilize(result_normal);
}