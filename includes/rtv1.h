#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "../libft/libft.h"
# include </home/dimas/Загрузки/fractol/Minilibx_Installer/minilibx/mlx.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4

# define USAGE 10
# define NO_CAMERA 11
# define NO_OBJECTS 12
# define PARAMETERS 13
# define NO_FD 14
# define INVALID 15

# define RED 16711680
# define GREEN 65280
# define BLUE 2831278
# define WHITE 16777214

# define WIN_SIZE_X	600
# define WIN_SIZE_Y	600
# define MAXDISTANCE 10000

# define PI 3.141592
# define FOV    45
# define CON_ANG 0.85

typedef struct		s_obj object;


typedef struct      s_vec
{
    double           i;
    double           j;
    double           k;
}                  vector;


typedef struct s_mlx
{
    int     bits_per_pixel;
    int     size_line;
    int     endian;
    void    *connection_id;
    void    *window_id;
    void    *image_id;
    char    *color_arr;

}               d_mlx;

typedef struct		s_camera
{
	vector          position;
    vector          rotation;
    int             count;
}					camera;

typedef struct		s_light
{
	vector          position;
    double			intensity;
}					t_light;

typedef struct		s_data
{
	camera		    camera;             //pointer??
	object			*objects_array;     
    t_light         *lights_array;
    float           *z_buffer;
	double			ambient;

	int				obj_count;
    int             light_count;
}					scene;

typedef struct		s_obj
{
    vector          *position;
    vector          *rotation;
	vector		    vector_color;
	double		    radius;
	int				color;
	int				type;
    float           current_t;
    int             object_index;
    int             refletcion;
    float           metallic;
    float           roughness;             

    float           (*ray_intersect)(vector *dir, vector *point, object *figure);
    void            (*find_normal)(vector *intersection_point, object *figure, vector *result_normal);
}					object;


vector create_vector(float i, float j, float k);

void make_circle(d_mlx *box, int i_pos, int j_pos, int r, int color);

void white_filler(d_mlx *box);

//sources

//cone

float find_b_cone(vector *point, vector *p1, vector *rot, vector *dir);

float find_c_cone(vector *point, vector *p1, vector *rot);

float	ray_intersect_cone(vector *dir, vector *point, object *obj);

void find_normal_cone(vector *intersection_point, object *figure, vector *result_normal);

//cylinder

float find_b_cyl(vector *point, vector *p1, vector *rot, vector *dir);

float find_c_cyl(vector *point, vector *p1, vector *rot, float radius);

float	ray_intersect_cylinder(vector *dir, vector *point, object *obj);

void find_normal_cylinder(vector *intersection_point, object *figure, vector *result_normal);

//plane

float	ray_intersect_pl(vector *dir, vector *point, object *object);

void find_normal_plane(vector *intersection_point, object *figure, vector *result_normal);

//sphere

vector	*cr_point(float i, float j, float k);

double	get_t(float a, float b, float d);

float sp_find_b(vector *point, vector *p1, vector *dir);

float sp_find_c(vector *point, vector *p1, float radius);

float	ray_intersect_sp(vector *dir, vector *point, object *object);

void find_normal_sphere(vector *intersection_point, object *figure, vector *result_normal);


//light_functions

int get_light(int start, int end, double percentage);

void get_vector_light(vector *start, vector *end, float percentage);

int get_diffuse_color(float offset, unsigned int color, unsigned int color2);

void add_specular(vector *diffuse, float spec, float NdotL);

int calculate_result_color(scene *scene, int i, float NdotL, float spec);

float saturate(float d);

vector *point_coords(vector *origin, float t, vector *dir);

int ft_icol(vector *col);

vector *ft_split_col(int color);

//render

void render(scene *scene, d_mlx *mlx);

vector *find_direction(int i, int j, scene *scene);

float cast_ray(vector *origin, vector *dir, scene *scene, unsigned int index);

float calculate_diffuse(scene *scene, vector *origin, vector *direction, object *figure);

float calculate_specular(scene *scene, vector *origin, vector *direction, object *figure);

vector *helper_for_casting(scene *scene, vector *direction, object *figure); // ????

float calculate_distance(vector *pos_light, vector *point);

int is_path_clear(vector *point, scene *scene, object *object, int light_index);

float find_diffuse(vector *point, scene *scene,  object *figure, int light_index);

float find_specular(vector *point, scene *scene,  object *figure, int light_index);

//vector_math

float	vector_length(vector *vec);

void	substr_vector_by_pointer(vector *vec1, vector *vec2, vector *result);

void    add_vector_by_pointer(vector *vec1, vector *vec2, vector *result);

vector	*substr_vector(vector *vec1, vector *vec2);

void	ft_normilize(vector *vec);

float	ft_scal(vector *vec1, vector *vec2);

void	vector_float_multiply(vector *vec, float mult, vector *result);

void vector_vector_multiply(vector *vec, vector *vec2, vector *result);

vector	*add_vector(vector *vec1, vector *vec2);

int		error_handler(char *error);

//vector_rotation           ?? pointer

vector	rotate_vector(vector dir, vector rot);

vector	rotate_i(vector dir, double angle);

vector	rotate_j(vector dir, double angle);

vector	rotate_k(vector dir, double angle);


// Parser functions

//init

int		init(d_mlx *data);

int		init_figur(scene *data, char *type, char *line, int object_index);

//parse

int		create_camera(scene *p, char **tab);

void	ambience(scene *p, char *s);

//read

int		read_file(d_mlx *init, scene *scene, char *file);

//light

t_light	*new_light(t_light l);

t_light		init_light(double x, double y, double z, double intens);

void	init_lights(scene *scene_obj, char **s, int light_index);

int		set_light(scene *scene_obj, char **tab, int light_index);

//object

object	*new_object(object new);

object	init_object_color(object *obj, double specular, char *color, int type);

object	*init_object(vector c, vector v, double a, double r);

int		create_object(scene *scene_obj, char *line);

int		count_object(char *file);

int		count_lights(char *file);

//utils

void free_tab(char **tab);

int len_tab(char **tab);

void check_tab_len(char **tab);

double ft_strtodbl(char *s);

int find_type(char *type);

double convert_to_rad(double a);

//error

int		error_output(int error);

void	scene_error(void);

//hook

int		escape(void);

int		key_press(int key, d_mlx *data);

#endif