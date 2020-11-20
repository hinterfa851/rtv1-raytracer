#include "../../includes/rtv1.h"

// CLEAR

int get_light(int start, int end, double percentage)        //clear
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int get_col(float offset, unsigned int color)   //clear
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

void ft_add_spec(t_vec *diffuse, float spec)
{
    spec = saturate(spec);
    diffuse->i += 255 * pow(spec, 80);
    diffuse->j += 255 * pow(spec, 80);
    diffuse->k += 255 * pow(spec, 80);                
}

int ft_calc_res(t_scene *scene, int i, float NdotL, float spec)     //clear
{
    t_vec *diffuse;
    int res;

    NdotL = saturate(NdotL);
    res = get_col(NdotL, scene->objs[i].color);
    diffuse = ft_split_col(res);
    ft_add_spec(diffuse, spec);
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

t_vec *point_coords(t_scene *scene, float t, t_vec *dir)
{
    t_vec *point;
    
    point = malloc(sizeof(t_vec));
    point->i = scene->cam->pos->i + t * dir->i;     
	point->j = scene->cam->pos->j + t * dir->j;
	point->k = scene->cam->pos->k + t * dir->k;
    return (point);
}

int ft_icol(t_vec *col)
{
    col->i = col->i < 255 ? col->i : 255;
    col->j = col->j < 255 ? col->j : 255;
    col->k = col->k < 255 ? col->k : 255;
    return(((int)col->i << 16) + ((int)col->j << 8) + (int)col->k);
}

t_vec *ft_split_col(int color)
{
    t_vec *res;

    res = malloc(sizeof(t_vec));
    res->i = color >> 16 & 0xFF;
    res->j = color >> 8 & 0xFF;
    res->k = color & 0xFF;
    return (res);
}
