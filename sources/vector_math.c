#include "../includes/rtv1.h"               //+-

float	vector_length(vector *vec)
{
	return (sqrt(vec->i * vec->i + vec->j * vec->j + vec->k * vec->k));
}

float	find_cos(vector *vec1, vector *vec2)
{
	return (ft_scal(vec1, vec2) / (vector_length(vec1) * vector_length(vec2)));
}

void add_vector_by_pointer(vector *vec1, vector *vec2, vector *result)
{
	result->i = vec1->i + vec2->i;
	result->j = vec1->j + vec2->j;
	result->k = vec1->k + vec2->k;
}

void substr_vector_by_pointer(vector *vec1, vector *vec2, vector *result)
{
	result->i = vec1->i - vec2->i;
	result->j = vec1->j - vec2->j;
	result->k = vec1->k - vec2->k;
}

vector	*substr_vector(vector *vec1, vector *vec2)
{
	vector *new_vector;

	new_vector = malloc(sizeof(vector));
	new_vector->i = vec1->i - vec2->i;
	new_vector->j = vec1->j - vec2->j;
	new_vector->k = vec1->k - vec2->k;
	return (new_vector);
}

vector	*add_vector(vector *vec1, vector *vec2)
{
	vector *new_vector;

	new_vector = malloc(sizeof(vector *));
	new_vector->i = vec1->i + vec2->i;
	new_vector->j = vec1->j + vec2->j;
	new_vector->k = vec1->k + vec2->k;
	return (new_vector);
}

void	ft_normilize(vector *vec)
{
	float length;

	length = vector_length(vec);
	vec->i /= length;
	vec->j /= length;
	vec->k /= length;
}

void vector_float_multiply(vector *vec, float mult, vector *result)
{
	result->i = vec->i * mult;
	result->j = vec->j * mult;
	result->k = vec->k * mult;
}

void vector_vector_multiply(vector *vec, vector *vec2, vector *result)
{
	result->i = vec->i * vec2->i;
	result->j = vec->j * vec2->j;
	result->k = vec->k * vec2->k;
}


float	ft_scal(vector *vec1, vector *vec2)
{
	return (vec1->i * vec2->i + vec1->j * vec2->j + vec1->k * vec2->k);
}

void	check_dir(vector *dir)
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