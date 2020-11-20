#include "../../includes/rtv1.h"

float find_xn(t_vec *v1, t_vec *v2, t_vec *v3)
{
	float res;

	res = v1->j * (v2->k - v3->k) + v2->j * (v3->k - v1->k) + v3->j * (v1->k - v2->k);
	return(res);
}

float find_yn(t_vec *v1, t_vec *v2, t_vec *v3)
{
	return(v1->k * (v2->i - v3->i) + v2->k * (v3->i - v1->i) + v3->k * (v1->i - v2->i));
}

float find_zn(t_vec *v1, t_vec *v2, t_vec *v3)
{
	return(v1->i * (v2->j - v3->j) + v2->i * (v3->j - v1->j) + v3->i * (v1->j - v2->j));
}

// void ft_set_normals(t_object *res, t_vec *v1, t_vec *v2, t_vec *v3)
// {
// 	t_vec *n;

// 	n = cr_point(0, 0, 0);
	
// 	res->p2->i = find_xn(v1, v2, v3);
// 	res->p2->j = find_yn(v1, v2, v3);
// 	res->p2->k = find_zn(v1, v2, v3);
// 	res->radius = v1->i * (v2->j * v3->k - v3->j * v2->k) + v2->i * (v3->j * v1->k - v1->j * v3->k) + v3->i * (v1->j * v2->k - v2->j * v1->k);
// }

void ft_set_point(t_vec *res, t_vec *start_p, t_vec *dir, float coef)
{
	
	res->i = start_p->i + dir->i * coef;
	res->j = start_p->j + dir->j * coef;
	res->k = start_p->k + dir->k * coef;
}
