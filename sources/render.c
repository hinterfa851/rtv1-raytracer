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

float random_float()
{
    int i;
    int j;

    srand(time(NULL));
    i = rand();
    j = rand();

//    srand48 drand48
    // srand48(time(NULL));
    
    // return (drand48());
    
    if (i < j)
        return(((float) i )/ ((float) j));
    else
        return(((float) j )/ ((float) i));
}

vector *random_point_in_sphere()
{
    vector *result;

    result = cr_point(random_float(), random_float(), random_float());
    // result->i = random_float();
    // result->j = random_float();
    // result->k = random_float();
    vector_float_multiply(result, 2, result);
    substr_vector(result, cr_point(1,1,1));
    while (vector_length(result) * vector_length(result) >= 1.0)
    {
        free(result);
        result = cr_point(random_float(), random_float(), random_float());
        vector_float_multiply(result, 2, result);
        substr_vector(result, cr_point(1,1,1));
    }
    return(result);
}

vector *fresnelSchlick(float cosTheta, vector *F0)
{
    vector *result;

    result = malloc(sizeof(vector));
    result->i = (1.0 - F0->i) * pow(1.0 - cosTheta, 5.0);
    result->j = (1.0 - F0->j) * pow(1.0 - cosTheta, 5.0);
    result->k = (1.0 - F0->k) * pow(1.0 - cosTheta, 5.0);

    add_vector_by_pointer(F0, result, result);
    return result;
}  

float DistributionGGX(vector *N, vector *H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = ft_scal(N, H);      // ??
    float NdotH2 = NdotH*NdotH;
	
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}
 
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;
 
    if (NdotV < 0)
        NdotV *= -1;
    float num = NdotV;
    float denom = NdotV * (1 - k) + k;      // negative val ruins everything
	
    return num / denom;
}

float GeometrySmith(vector *N, vector *V, vector *L, float roughness)
{
    float NdotV =  ft_scal(N, V);          //  ??
    float NdotL =  ft_scal(N, L);          // ??
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vector *helper(vector *origin, vector *direction, vector *point, object *figure)
{
    vector *light_color;
    vector *result_color;
    vector *normal;
    vector *L;
    vector *radiance;
    vector *obj_col;
    vector *F0;
    vector *F;
    vector *V;
    vector *H;
    vector *kD;
    vector *single;

    vector *numerator;
    vector *specular;
    float denominator;
    vector *light_pos;
    vector *test;

    float attenuation;
    float distance;
    float NdotL;

    // float metallic = 0;
    // float roughness = 0;

    float metallic = figure->metallic ;
    float roughness = figure->roughness ;


    if (roughness == 0)     // bad issue solving
        roughness = 0.06;

    result_color = malloc(sizeof(vector));
    normal = malloc(sizeof(vector));
    // radiance = malloc(sizeof(vector));
    radiance = cr_point(1,1,1);                 //????
    light_color = cr_point(1,1,1);
 //   light_color = cr_point(0.3,0.12, .94);            blue
    single = cr_point(1, 1, 1);
//    obj_col = cr_point(0.47, 0.39, 0.39);
    // obj_col = cr_point(0.72, 0.06, 0.06);
     obj_col = cr_point(1, 0, 0);
    
    numerator = malloc(sizeof(vector));
    specular = malloc(sizeof(vector));
    test = malloc(sizeof(vector));
    light_pos = cr_point(50, 50, -100);
 //   light_pos = cr_point(0, 0, -100);

    V = substr_vector(light_pos, point);
    ft_normilize(V);

    F0 = cr_point(0.04, 0.04, 0.04);

    get_vector_light(F0, obj_col, metallic);

  
    L = substr_vector(light_pos, point);   // light in first arg
    distance = vector_length(L);
    attenuation = 1 / (distance * distance);
    attenuation = 1;
    ft_normilize(L);
    H = add_vector(V, L);
    ft_normilize(H);

    
  
    vector_float_multiply(light_color, attenuation, radiance);
    figure->find_normal(point, figure, normal);
    NdotL = saturate(-1 * ft_scal(normal, L));

    

    //Cook-Torrance
    float NDF = DistributionGGX(normal, H, roughness);
    float G = GeometrySmith(normal, V, L, roughness);
    F = fresnelSchlick(ft_scal(H, V), F0);

    // vec ks = F;
    kD = substr_vector(single, F);
    vector_float_multiply(kD, 1 - metallic, kD);

    vector_float_multiply(F, NDF * G, numerator);
    denominator = 4.0 * ft_scal(normal, V)  * ft_scal(normal, L); //??
    if (!denominator)
        denominator = 0.001;
    vector_float_multiply(numerator, 1.0 / denominator, specular);

 //   vector_float_multiply(specular, 0.1, specular);
    
    vector_vector_multiply(kD, obj_col, test);
    vector_float_multiply(test, 1.0/3.14, test);

    add_vector_by_pointer(test, specular, test);
 //           printf("res - r, g, b - %f, %f, %f\n", NDF, G, test->k);   

//            printf("res - r, g, b - %f, %f, %f\n", specular->i, specular->j, specular->k);   
 //           printf("res - r, g, b - %f, %f, %f\n", test->i, test->j, test->k);   

    vector_float_multiply(test, NdotL, test);
    vector_vector_multiply(test, radiance, test);



    result_color->i = test->i;
    result_color->j = test->j;
    result_color->k = test->k;

    result_color->i /= result_color->i + 1;
    result_color->j /= result_color->j + 1;
    result_color->k /= result_color->k + 1;

    result_color->i = pow(result_color->i, 1.0 / 2.2);
    result_color->j  = pow(result_color->j, 1.0 / 2.2);
    result_color->k  = pow(result_color->k, 1.0 / 2.2);

    // ambient
    vector_float_multiply(obj_col, 0.1, obj_col);
    add_vector_by_pointer(result_color, obj_col, result_color);
    
    vector_float_multiply(result_color, 256, result_color);

 //   printf("res - r, g, b - %f, %f, %f\n", result_color->i, result_color->j, result_color->k);

    free(kD);
    free(radiance);
    free(L);
    free(normal);
    free(light_color);
    free(obj_col);
    free(F0);
    free(V);
    free(single);
    free(specular);
    free(H);
    free(F);
    free(test);
    free(light_pos);
    return(result_color);
}

float cast_ray(vector *origin, vector *dir, scene *scene, unsigned int index)
{
    // t - distance from camera to intersection point
    float t;
    int i;
    float result;
    float diffuse;
    float specular;
    vector *test;
    vector *intersection_point;
    vector normal;
    vector *rando_vec;
    vector *cons;

    i = 0;
    result = WHITE;
   test = malloc(sizeof(vector));
    cons = cr_point(0.01, 0.01, 0.01);
    while (i < scene->obj_count)
    {
        if ((t = scene->objects_array[i].ray_intersect(dir, origin, &scene->objects_array[i])))      // not optimized algorithm
        {            
            // mb would be better to add object to list and then find lowest t before color calculating
       //      if (t <= scene->z_buffer[index])
       //      {
         //       scene->z_buffer[index] = t;
                intersection_point = point_coords(origin, t, dir);
                scene->objects_array[i].find_normal(intersection_point, &scene->objects_array[i], &normal);
                rando_vec = random_point_in_sphere();
                add_vector_by_pointer(intersection_point, &normal, test);
                add_vector_by_pointer(test, rando_vec,test);
       //         return 0x000000;
                vector_float_multiply(&normal, -0.1, &normal);
                add_vector_by_pointer(intersection_point, &normal, intersection_point);
                free(rando_vec);
                free(cons);
                
                vector_float_multiply(&normal, -1, &normal);
 //               return 0.5 * ft_scal(&normal, dir) * cast_ray(intersection_point, test, scene, index);               
 //               return get_diffuse_color( 10 * ft_scal(&normal, dir), cast_ray(intersection_point, test, scene, index), 0x000000);               
 //               return get_diffuse_color(  10 * ft_scal(&normal, dir), 0xffffff, 0x000000);
                return ft_icol(helper(origin, dir, intersection_point, &scene->objects_array[i]));


 //               scene->objects_array[i].current_t = t; 
            //        diffuse = calculate_diffuse(scene, origin, dir, &scene->objects_array[i]);
              //      specular = calculate_specular(scene, origin, dir, &scene->objects_array[i]);
              //      result = calculate_result_color(scene, i, diffuse, specular);
              
     //           result = 0xFFFFFF;
       //      }
        }
        i++;
    }

    float t_val = 0.5 * (dir->j/vector_length(dir) + 1);
//     vector *vec1 = cr_point(1, 1, 1);
//     vector_float_multiply(vec1, 1 - t_val, vec1);
//     vector *vec2 = cr_point(0.5, 0.7, 1);
//     vector_float_multiply(vec2, t_val, vec2);
//     add_vector_by_pointer(vec1, vec2, vec1);
//     result = ft_icol(vec1);
//     free(vec1);
//     free(vec2);
//   //  printf("%d\tt - %f\n", result, t_val);
    result = get_diffuse_color(1 - t_val, WHITE, 0x0b3cb8);
    free(cons);
    result = 0x000000;
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