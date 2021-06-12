#include "../includes/rtv1.h"

vector	*cr_point(float i, float j, float k)
{
	vector *ball;

	if (!(ball = malloc(sizeof(vector))))
		error_handler("memory error");
	ball->i = i;
	ball->j = j;
	ball->k = k;
	return (ball);
}

double	get_t(float a, float b, float d)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		return (t2);
	return (-1);
}

float sp_find_b(vector *point, vector *p1, vector *dir)
{
	float res;
	vector *a;

	a = substr_vector(point, p1);
	res = 2 * ft_scal(dir, a);
	free(a);
	return (res);
}

float sp_find_c(vector *point, vector *p1, float radius)
{
	float res;
	vector *a;
	vector *b;

	a = substr_vector(point, p1);
	b = substr_vector(point, p1);
	res = ft_scal(a, b) - radius * radius;
	free(a);
	free(b);
	return (res);
}

float	ray_intersect_sp(vector *dir, vector *point, object *object)
{
	float a;
	float b;
	float c;
	float d;
	float t;

	a = ft_scal(dir, dir);
	b = sp_find_b(point, object->position, dir);
	c = sp_find_c(point, object->position, object->radius);
	d = b * b - 4 * a * c;
	t = d < 0 ? -1 : get_t(a, b, d);
	if (t < 0)
		return (0);
	return (t);
}

void find_normal_sphere(vector *intersection_point, object *figure, vector *result_normal)
{
	substr_vector_by_pointer(figure->position, intersection_point, result_normal);
	ft_normilize(result_normal);
}