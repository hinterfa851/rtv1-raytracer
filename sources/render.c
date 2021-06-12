#include "../includes/rtv1.h"

vector *find_direction(int i, int j, scene *scene)
{
    //making greed in  0, 0
    vector *greed_point;
    vector *camera_pos;
    vector *direction;
    float angle;

    angle = tan(M_PI * 0.5 * FOV / 180.);
    camera_pos = cr_point(0, 0, 0);
    greed_point = malloc(sizeof(vector *));
    greed_point->i = (2 * ((i + 0.5) / WIN_SIZE_X) - 1) * angle * WIN_SIZE_X / WIN_SIZE_Y;
    greed_point->j = (1 - 2 * ((j + 0.5) / WIN_SIZE_Y)) * angle;
    greed_point->k = 1;
    direction = substr_vector(greed_point, camera_pos);
    ft_normilize(direction);
    *direction = rotate_vector(*direction, scene->camera.rotation);
    free(greed_point);
    free(camera_pos);
    return(direction);
}


// calculation all pixels in frame
// by creating direction and casting
void render(scene *scene, d_mlx *mlx)
{
    vector *direction;
    int j;
    int i;

    i = 0;
    j = 0;
    printf("lights count - %i\n", scene->light_count);
    printf("i, j, k - %f\t%f\t%f\n", scene->objects_array[i].rotation->i, scene->objects_array[i].rotation->j, scene->objects_array[i].rotation->k);
    while(j < WIN_SIZE_Y)
    {
        while(i < WIN_SIZE_X)
        {
            direction = find_direction(i, j, scene);        // change scene to scene->camera
            *(int *)(mlx->color_arr + (i + j * WIN_SIZE_X) * (mlx->bits_per_pixel/ 8)) = cast_ray(&scene->camera.position, direction, scene, j * WIN_SIZE_X + i);
            free(direction); 
            i++;
        }
        i = 0;
        j++;
    }
}

vector *reflect(vector *dir, vector *normal)
{
    vector *result;
    vector for_calc;
    float   c;

    vector_float_multiply(normal, 2 * ft_scal(dir, normal), &for_calc);
    result = substr_vector(dir, &for_calc);
    return (result);
}

float cast_ray(vector *origin, vector *dir, scene *scene, unsigned int index)
{
    // t - distance from camera to intersection point
    float t;
    int i;
    int result;
    float diffuse;
    float specular;

    i = 0;
    result = 0x000000;
    while (i < scene->obj_count)
    {
        if ((t = scene->objects_array[i].ray_intersect(dir, origin, &scene->objects_array[i])))      // not optimized algorithm
        {            
            // mb would be better to add object to list and then find lowest t before color calculating
             if (t <= scene->z_buffer[index])
   //          if (t)     //?????
             {
                scene->z_buffer[index] = t;
                scene->objects_array[i].current_t = t; 
                if (!scene->objects_array[i].refletcion)       
                {
                    diffuse = calculate_diffuse(scene, origin, dir, &scene->objects_array[i]);
                    specular = calculate_specular(scene, origin, dir, &scene->objects_array[i]);
                    result = calculate_result_color(scene, i, diffuse, specular);
                }
                else
                {
                    vector *intersection_point;
                    vector normal;
                    vector *reflected_dir;
                    vector test;
                    vector *result_point;
                    float res;

                    intersection_point = point_coords(origin, scene->objects_array[i].current_t, dir);
                    scene->objects_array[i].find_normal(intersection_point, &scene->objects_array[i], &normal);
                    reflected_dir = reflect(dir, &normal);
                    ft_normilize(reflected_dir);
                    vector_float_multiply(&normal, 1e-3,&test);
                    result_point = (ft_scal(reflected_dir, &normal) < 0) ? substr_vector(intersection_point,&test) : add_vector(intersection_point,&test);
                    res = cast_ray(result_point, reflected_dir,scene, index);
    //                printf("%f\n", res);
                    return (res);
                }
     //           result = 0xFFFFFF;
             }
        }
        i++;
    }
    return(result);
}

float calculate_distance(vector *pos_light, vector *point)
{
    float res;
    vector *a;

    a = substr_vector(pos_light, point);
    res = vector_length(a);
    free(a);
    return (res);
}

int is_path_clear(vector *point, scene *scene, object *object, int light_index)
{
    vector *NewDir;
    int j;
    int res;

    j = 0;
    res = 0;
    NewDir = substr_vector(&scene->lights_array[light_index].position, point);
    while (j < scene->obj_count)
    {
        if (j != object->object_index)
        {
            if(scene->objects_array[j].ray_intersect(NewDir, point, &scene->objects_array[j]))
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