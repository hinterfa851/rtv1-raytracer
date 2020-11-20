#include "../../includes/rtv1.h"

void render(t_scene *scene, t_mx *box)     // clear
{
    int j;
    int i;
    // float angle;

    i = 0;
    j = 0;
    scene->cam->pos->i += 0;
    // angle = tan(M_PI * 0.5 * FOV / 180.);
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
 //   free(scene->light);
  //  freesher_for_scene(scene);
  //  free(scene);
}

void helper_for_render(int i, int j, t_scene *scene,  t_mx *box)   //+-
{
    t_vec *greed_point;
    t_vec *cam;
    t_vec *dir;
    float angle;

    // printf("helper for render\n");
    angle = tan(M_PI * 0.5 * FOV / 180.);
    cam = cr_point(0, 0, 0);
    greed_point = cr_point(((float)2*(i - 1/2)/WIDTH - 1), ((float)2*(j - 1/2)/WIDTH - 1), 1);
    greed_point->i = (2 * ((i + 0.5) / WIDTH) - 1) * angle * WIDTH / HEIGHT;
    greed_point->j = (1 - 2 * ((j + 0.5) / HEIGHT)) * angle;
    greed_point->k = 1;
    dir = ft_substr(greed_point, cam);  // del
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
    t_vec *test;

    i = 0;
    res = 0x000000;
    // printf("cast ray\n");
    sender = malloc(sizeof(t_vec));
    while (i < scene->obj_count)
    {
        if ((t = scene->objs[i].ray_intersect(dir, scene->cam->pos, scene->objs[i]))) //нахожу пересечение для всех обьектов
        {
            //  printf("catch intersection\n");
             if (t <= scene->z_buffer[index])   // если обьект ближе всех к камере - смотрю цвет
             {
                scene->z_buffer[index] = t;
                sender->j = t;           // t num
                sender->i = i;          // obj num
                values = helper_for_casting(sender, scene, dir, index);
                res = ft_calc_res(scene, i, values->i, values->j);
                test = ft_split_col(res);
                // printf("%f\t%f\n", values->i, values->j);
//                printf("%f\t%f\t%f\n", test->i, test->j, test->k);
                free(values);
             }
            // res = 0xffffff;
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
    // printf("helper for castinf\n");
    point = point_coords(scene, sender->j, dir);    //??
    // printf("helper for castinf\n");
    res = malloc(sizeof(t_vec));        // ok
    res->i = 0;
    res->j = 0;
    // distance = 0;
    k = 0;
 //   distance = ft_vec_len(ft_substr(scene->light[k].pos, point));
//  printf("helper for castinf\n");
    distance = calc_dist(scene->light[k].pos, point);
    // printf("helper for castinf\n");
    // printf("%f\n", distance);
     while (k < scene->light_count)
    {
        if (path_clear(point, scene, sender->i, k) || fabs(sender->j - scene->z_buffer[index]) == 0)
        {
            // printf("helper for casting inner\n");
            input = scene->objs[(int)sender->i].color_find(point, scene, sender, k);
            res->i += input->i * scene->light[k].power / (distance * distance);
            res->j += input->j;
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

    // printf("%f\t%f\t%f\n", pos_light->i, pos_light->j, pos_light->k);
    // printf("calc_dist\n");
    a = ft_substr(pos_light, point);
    // printf("calc_dist2\n");
    res = ft_vec_len(a);
    // printf("calc_dist3\n");
    free(a);
    return (res);
}

int path_clear(t_vec *point, t_scene *scene, int i, int k)      // +-
{
    t_vec *NewDir;
    int j;
    int res;

    j = 0;
    res = 0;
  //  NewDir = ft_substr(point, scene->light.pos);
    NewDir = ft_substr(scene->light[k].pos, point);
    while (j < scene->obj_count)
    {
        // if  (scene->objs[j].p1 != scene->objs[i].p1)
        //     printf("got it!\n");
        if (j != i )
        {
   //         printf("in func\n");
            if(scene->objs[j].ray_intersect(NewDir, point, scene->objs[j]))
            {
  //              printf("catch\n");
                // if (scene->objs[j].p1 != scene->objs[i].p1)
                // {
                //     printf("catch\n");
                free(NewDir);
                    return(0);

                // }
            }
 //           free(NewDir);
        }
        j++;
    }
    return (1);
}