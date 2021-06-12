#include "../includes/rtv1.h"

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int get_diffuse_color(float offset, unsigned int color)
{
    int     red;
    int     green;
    int     blue;
    int     c1;
    int     c2;

    c2 = color;
    c1 = 0x000000;
    red = get_light((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, offset);
    green = get_light((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, offset);
    blue = get_light(c1 & 0xFF, c2 & 0xFF, offset);
    return ((red << 16) | (green << 8) | blue);
}

void add_specular(vector *diffuse, float spec, float NdotL)
{
    spec = saturate(spec);
    diffuse->i += 255 * spec * NdotL;
    diffuse->j += 255 * spec * NdotL;
    diffuse->k += 255 * spec * NdotL;                
}

int calculate_result_color(scene *scene, int i, float NdotL, float spec)
{
    vector *diffuse;
    int res;

    NdotL = saturate(NdotL);
 //   res = get_diffuse_color(NdotL, scene->objects_array[i].color);
 //   res = NdotL * scene->objects_array[i].color;
  //  res = scene->objects_array[i].color;
    diffuse = ft_split_col(scene->objects_array[i].color);
    vector_float_multiply(diffuse, NdotL, diffuse);
 //   add_specular(diffuse, spec, NdotL);
    res = ft_icol(diffuse);
    free(diffuse);
    return (res);
}

float saturate(float d)
{
    if (d < 0)
        return 0;
    if (d > 1)
        return 1;
    return (d);
}

vector *point_coords(vector *origin, float t, vector *dir)
{
    vector *point;
    
    point = malloc(sizeof(vector));
    point->i = origin->i + t * dir->i;     
	point->j = origin->j + t * dir->j;
	point->k = origin->k + t * dir->k;
    return (point);
}

int ft_icol(vector *col)
{
    col->i = col->i < 255 ? col->i : 255;
    col->j = col->j < 255 ? col->j : 255;
    col->k = col->k < 255 ? col->k : 255;
    return(((int)col->i << 16) + ((int)col->j << 8) + (int)col->k);
}

vector *ft_split_col(int color)
{
    vector *res;

    res = malloc(sizeof(vector));
    res->i = color >> 16 & 0xFF;
    res->j = color >> 8 & 0xFF;
    res->k = color & 0xFF;
    return (res);
}
