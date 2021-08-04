#include "../includes/rtv1.h"

float calculate_diffuse(scene *scene,vector *origin, vector *direction, object *figure)
{
//    int light_index;
    vector *intersection_point;
    float distance;
    float result;
    float result_per_light;

    intersection_point = point_coords(origin, figure->current_t, direction);
//    light_index = 0;
    result = 0;
    // while (light_index < scene->light_count)
    // {
        distance = calculate_distance(&scene->camera.position, intersection_point);
        // if (is_path_clear(point, scene, figure, light_index))
        // {
 //           result = 1;
//            result_per_light = find_diffuse(intersection_point, scene, figure, light_index);
            result_per_light = find_diffuse(intersection_point, scene, figure, 0);
            if (result_per_light > 0)
            {
     //           result_per_light *= scene->lights_array[light_index].intensity / (distance * distance);
                result += result_per_light;
            }
 //       }
       // light_index++;
//    }
//    result += 0.1;  // adding ambient lighting
    free(intersection_point);
    return (result);
}

float calculate_specular(scene *scene, vector *origin, vector *direction, object *figure)
{
    int light_index;
    vector *intersection_point;
    float result;
    float result_per_light;

    intersection_point = point_coords(origin, figure->current_t, direction);
    light_index = 0;
    result = 0;
    while (light_index < scene->light_count)
    {
        // if (is_path_clear(point, scene, figure, light_index))
        // {
            result_per_light = find_specular(intersection_point, scene, figure, light_index);
            result_per_light = pow(result, 80);
 //       }
        light_index++;
        result += result_per_light;
    }
    free(intersection_point);
    return (result);
}

float find_diffuse(vector *point, scene *scene,  object *figure, int light_index)
{
	vector normal;
	vector light_to_point;
	vector camera_to_point;

	figure->find_normal(point, figure, &normal);
    
    substr_vector_by_pointer(point, &scene->lights_array[light_index].position, &light_to_point);
	substr_vector_by_pointer(point, &scene->camera.position, &camera_to_point);
	ft_normilize(&normal);
	ft_normilize(&light_to_point);
	return (ft_scal(&normal, &light_to_point));

}

float find_specular(vector *point, scene *scene,  object *figure, int light_index)
{
	vector normal;
	vector light_to_point;
	vector camera_to_point;
	vector halfway_vector;

	figure->find_normal(point, figure, &normal);
    substr_vector_by_pointer(point, &scene->lights_array[light_index].position, &light_to_point);
	substr_vector_by_pointer(point, &scene->camera.position, &camera_to_point);
	ft_normilize(&normal);
	ft_normilize(&light_to_point);
	ft_normilize(&camera_to_point);
	add_vector_by_pointer(&camera_to_point, &light_to_point, &halfway_vector);
	ft_normilize(&halfway_vector);
	return (ft_scal(&halfway_vector, &normal));
}