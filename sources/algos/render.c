#include "../../includes/rtv1.h"

void render(t_scene *scene, t_mx *box)
{
    int j;
    int i;

    i = 0;
    j = 0;
    scene->cam->pos->i += 0;
    while(j < HEIGHT)
    {
        while(i < WIDTH)
        {
            helper_for_render(i, j, scene, box);
            i++;
        }
        i = 0;
        j++;
    }
}

void helper_for_render(int i, int j, t_scene *scene,  t_mx *box)
{
    t_vec *greed_point;
    t_vec *cam;
    t_vec *dir;
    float angle;

    angle = tan(M_PI * 0.5 * FOV / 180.);
    cam = cr_point(0, 0, 0);
    greed_point = cr_point(((float)2*(i - 1/2)/WIDTH - 1), ((float)2*(j - 1/2)/WIDTH - 1), 1);
    greed_point->i = (2 * ((i + 0.5) / WIDTH) - 1) * angle * WIDTH / HEIGHT;
    greed_point->j = (1 - 2 * ((j + 0.5) / HEIGHT)) * angle;
    greed_point->k = 1;
    dir = ft_substr(greed_point, cam);
    ft_normilize(dir);
    *dir = vec_rot(*dir, *(scene->cam->dir));
    ft_normilize(dir);
    *(int *)(box->draw_arr + (i + j * WIDTH) * (box->bits_per_pixel / 8)) = cast_ray(dir, scene, j * WIDTH + i);
    free(greed_point);
    free(cam);
    free(dir);
}

float cast_ray(t_vec *dir, t_scene *scene, unsigned int index)
{
    float t;
    int i;
    int res;
    t_vec *values;
    t_vec *sender;

    i = 0;
    res = 0x000000;
    sender = malloc(sizeof(t_vec));
    while (i < scene->obj_count)
    {
        if ((t = scene->objs[i].ray_intersect(dir, scene->cam->pos, scene->objs[i])))
        {
             if (t <= scene->z_buffer[index])
             {
                scene->z_buffer[index] = t;
                sender->j = t;
                sender->i = i;
                values = helper_for_casting(sender, scene, dir, index);
                res = ft_calc_res(scene, i, values->i, values->j);
                free(values);
             }
        }
        i++;
    }
    free(sender);
    return(res);
}

t_vec *helper_for_casting(t_vec *sender, t_scene *scene, t_vec *dir, unsigned int index)
{
    int k;
    t_vec *point;
    float distance;
    t_vec *res;
    t_vec *input;

    index += 0;
    point = point_coords(scene, sender->j, dir);
    res = malloc(sizeof(t_vec));
    res->i = 0;
    res->j = 0;
    k = 0;
    while (k < scene->light_count)
    {
        distance = calc_dist(scene->light[k].pos, point);
        if (path_clear(point, scene, sender->i, k))
        {
            input = scene->objs[(int)sender->i].color_find(point, scene, sender, k);
            res->i += input->i * scene->light[k].power / (distance * distance);
            res->j += pow(input->j, 80);
            free(input);
        }
        k++;
    }
    free(point);
    return (res);
}

float calc_dist(t_vec *pos_light, t_vec *point)
{
    float res;
    t_vec *a;

    a = ft_substr(pos_light, point);
    res = ft_vec_len(a);
    free(a);
    return (res);
}

int path_clear(t_vec *point, t_scene *scene, int i, int k)
{
    t_vec *NewDir;
    int j;
    int res;

    j = 0;
    res = 0;
    NewDir = ft_substr(scene->light[k].pos, point);
    while (j < scene->obj_count)
    {
        if (j != i)
        {
            if(scene->objs[j].ray_intersect(NewDir, point, scene->objs[j]))
            {
                free(NewDir);
                return(0);
            }
        }
        j++;
    }
    free(NewDir);
    return (1);
}