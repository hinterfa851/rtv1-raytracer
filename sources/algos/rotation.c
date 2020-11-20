#include "../../includes/rtv1.h"

t_vec	rot_i(t_vec dir, double angle)
{
	t_vec res;

	angle = ((double)angle * (M_PI / 180));
	res.i = dir.i;
	res.j = dir.j * cos(angle) + dir.k * sin(angle);
	res.k = -1 * dir.j * sin(angle) + dir.k * cos(angle);
	return (res);
}

t_vec	rot_j(t_vec dir, double angle)
{
	t_vec res;

	angle = ((double)angle * (M_PI / 180));
	res.i = dir.i * cos(angle) + dir.k * sin(angle);
	res.j = dir.j;
	res.k = -1 * dir.i * sin(angle) + dir.k * cos(angle);
	return (res);
}

t_vec	rot_k(t_vec dir, double angle)
{
	t_vec res;

	angle = ((double)angle * (M_PI / 180));
	res.i = dir.i * cos(angle) + dir.j * sin(angle);
	res.j = -1 * dir.i * sin(angle) + dir.j * cos(angle);
	res.k = res.k;
	return (res);
}

t_vec	vec_rot(t_vec dir, t_vec rot)
{
	dir = rot_i(dir, rot.i);
	dir = rot_j(dir, rot.j);
	dir = rot_k(dir, rot.k);
	return (dir);
}
