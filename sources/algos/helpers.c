#include "../../includes/rtv1.h"

float	ft_vec_len(t_vec *vec)
{
	return (sqrt(vec->i * vec->i + vec->j * vec->j + vec->k * vec->k));
}

float	find_cos(t_vec *vec1, t_vec *vec2)
{
	return (ft_scal(vec1, vec2) / (ft_vec_len(vec1) * ft_vec_len(vec2)));
}

float	find_cos2(int i1, int j1, int k1, int i2, int j2, int k2)
{
	float res;

	res = i1 * i2 + j1 * j2 + k1 * k2;
	res /= sqrt(i1 * i1 + j1 * j1 + k1 * k1) * sqrt(i2 * i2 + j2 * j2 + k2 * k2);
	return (res);
}

void	ft_normilize(t_vec *vec)
{
	float len;

	len = ft_vec_len(vec);
	vec->i /= len;
	vec->j /= len;
	vec->k /= len;
}

t_vec	*ft_vec_mult(t_vec *vec, float mult)
{
	vec->i *= mult;
	vec->j *= mult;
	vec->k *= mult;
	return (vec);
}

t_vec	*ftm_vec_mult(t_vec *vec, float mult)
{
	t_vec *test;

	test = malloc(sizeof(t_vec));
	test->i = vec->i * mult;
	test->j = vec->j * mult;
	test->k = vec->k * mult;
	return (test);
}

t_vec	*ft_substr(t_vec *vec1, t_vec *vec2)
{
	t_vec *nw;

	nw = malloc(sizeof(t_vec *));
	nw->i = vec1->i - vec2->i;
	nw->j = vec1->j - vec2->j;
	nw->k = vec1->k - vec2->k;
	return (nw);
}

t_vec	*ft_add_vec(t_vec *vec1, t_vec *vec2)
{
	t_vec *nw;

	nw = malloc(sizeof(t_vec *));
	nw->i = vec1->i + vec2->i;
	nw->j = vec1->j + vec2->j;
	nw->k = vec1->k + vec2->k;
	return (nw);
}

t_vec	*ftm_add_vec(t_vec *vec1, t_vec *vec2)
{
	t_vec *nw;

	nw = malloc(sizeof(t_vec *));
	nw->i = vec1->i + vec2->i;
	nw->j = vec1->j + vec2->j;
	nw->k = vec1->k + vec2->k;
	return (nw);
}

float	ft_scal(t_vec *vec1, t_vec *vec2)
{
	return (vec1->i * vec2->i + vec1->j * vec2->j + vec1->k * vec2->k);
}

void	check_dir(t_vec *dir)
{
	float res;

	res = sqrt(dir->i * dir->i + dir->j * dir->j + dir->k * dir->k);
}

int		error_handler(char *error)
{
	ft_putendl(error);
	exit(1);
	return (1);
}
