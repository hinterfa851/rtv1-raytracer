#include "../includes/rtv1.h"

float	ray_intersect_pl(vector *dir, vector *point, object *object)
{
	float res;
	vector *x;

	x = substr_vector(point, object->position);
	res = -1 * ft_scal(x, object->rotation) / ft_scal(dir, object->rotation);
	free(x);
	if (res < 0)
		return (0);
	return (res);
}

void find_normal_plane(vector *intersection_point, object *figure, vector *result_normal)
{
	*result_normal = rotate_vector(*figure->rotation, *cr_point(0, 0, 1));
}