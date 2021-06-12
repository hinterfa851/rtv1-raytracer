#include "../includes/rtv1.h"                           // -+

vector	rotate_vector(vector dir, vector rot)       // mb pointer???
{
	dir = rotate_i(dir, rot.i);
	dir = rotate_j(dir, rot.j);
	dir = rotate_k(dir, rot.k);
	return (dir);
}

vector	rotate_i(vector dir, double angle)
{
	vector result;

	angle = ((double)angle * (M_PI / 180));
	result.i = dir.i;
	result.j = dir.j * cos(angle) + dir.k * sin(angle);
	result.k = -1 * dir.j * sin(angle) + dir.k * cos(angle);
	return (result);
}

vector	rotate_j(vector dir, double angle)
{
	vector result;

	angle = ((double)angle * (M_PI / 180));
	result.i = dir.i * cos(angle) + dir.k * sin(angle);
	result.j = dir.j;
	result.k = -1 * dir.i * sin(angle) + dir.k * cos(angle);
	return (result);
}

vector	rotate_k(vector dir, double angle)
{
	vector result;

	angle = ((double)angle * (M_PI / 180));
	result.i = dir.i * cos(angle) + dir.j * sin(angle);
	result.j = -1 * dir.i * sin(angle) + dir.j * cos(angle);
	result.k = dir.k;
	return (result);
}