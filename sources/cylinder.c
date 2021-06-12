#include "../includes/rtv1.h"

float find_b_cyl(vector *point, vector *p1, vector *rot, vector *dir)
{
	float res;
	vector *to_del;

	to_del = substr_vector(point, p1);
	res = 2 * (ft_scal(dir, to_del) - ft_scal(dir, rot) * ft_scal(to_del, rot));
	free(to_del);
	return (res);
}

float find_c_cyl(vector *point, vector *p1, vector *rot, float radius)
{
	float res;
	vector *to_del;

	to_del = substr_vector(point, p1);
	res = ft_scal(to_del, to_del) - ft_scal(to_del, rot) * ft_scal(to_del, rot) - radius * radius;
	free(to_del);
	return (res);
}

float	ray_intersect_cylinder(vector *dir, vector *point, object *obj)
{
	float a;
	float b;
	float c;
	float d;
	float t;

	a = ft_scal(dir, dir) - ft_scal(dir, obj->rotation)
	* ft_scal(dir, obj->rotation);
	b = find_b_cyl(point, obj->position, obj->rotation, dir);
	c = find_c_cyl(point, obj->position, obj->rotation, obj->radius);
	d = b * b - 4 * a * c;
	t = d < 0 ? -1 : get_t(a, b, d);
	if (t < 0)
		return (0);
	return (t);
}

void find_normal_cylinder(vector *intersection_point, object *figure, vector *result_normal)
{
	vector axis_point;
	vector vec;
	float koef;

	koef = (ft_scal(figure->rotation, intersection_point) - ft_scal(figure->rotation, figure->position)) / (ft_scal(figure->rotation, figure->rotation));
	vector_float_multiply(figure->rotation, koef, &vec);
	add_vector_by_pointer(figure->position, &vec, &axis_point);
	substr_vector_by_pointer(&axis_point, intersection_point, result_normal);
	ft_normilize(result_normal);
}
