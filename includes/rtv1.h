/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:20:11 by glychest          #+#    #+#             */
/*   Updated: 2020/11/20 16:08:35 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

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

# define WIDTH 900
# define HEIGHT 900
# define FOV    90
# define RADIUS	10
# define LENGTH 100
# define CAM_D	200
# define MAXDISTANCE 10000
# define CON_ANG 0.85

# define RED 16711680
# define GREEN 65280
# define BLUE 2831278

# define WIN_SIZE_X	900
# define WIN_SIZE_Y	900


# define PI 3.141592

typedef struct		s_object t_object;

typedef struct      s_vec
{
    float           i;
    float           j;
    float           k;
}                  t_vec;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_light
{
	double			x;
	double			y;
	double			z;
	double			intens;
}					t_light;

typedef struct      s_li
{
    t_vec			*pos;
    float			power;
}                  t_li;

typedef struct		s_obj
{
	t_vector		c;
	t_vector		v;
	double			a;
	double			r;
	double			specular;
	int				color;
	int				type;
}					t_obj;


typedef struct		s_camera
{
	double			x;
	double			y;
	double			z;
	int				canv_h;
	int				canv_w;
	int				canv_d;
	int				cam;
}					t_camera;

typedef struct      s_cam
{
    t_vec			*pos;
    t_vec			*dir;
}                  t_cam;

typedef struct		s_img
{
	void			*img;
	int				bit_per_pixel;
	int				size_line;
	int				endline;
	char			*img_data;
}					t_img;

typedef struct		s_mlx
{
	void			*win;
	void			*mlx;
}					t_mlx;

typedef struct		s_data
{
	t_mlx			mlx;
	t_img			img;
	t_img			canv;
	t_camera		camera;
	t_obj			*objs;
	t_list			*figur;
	t_list			*light;
	double			ambient;
	int				obj_n;
	int				fd;
}					t_data;

typedef struct		s_mx
{
	void		*conn_id;
	void		*win_id;
	char		*draw_arr;
	void		*image_id;
	int			endian;
	int			size_line;
	int			bits_per_pixel;
}					t_mx;

typedef struct      s_scene
{
    t_cam           *cam;
    t_li            *light;
    t_object        *objs;
    float           *z_buffer;
    int             obj_count;
    int             light_count;
    int             memory;
}                   t_scene;

typedef struct      s_object
{
    t_vec           *p1;
    t_vec           *rot;
    t_vec           col;
    float           radius;
    unsigned int    color;

    float           (*ray_intersect)(t_vec *dir, t_vec *point, t_object object);
    t_vec           *(*color_find)(t_vec *point, t_scene *scene, t_vec *sender, int k);

}                   t_object;

t_object	cr_sphere(t_vec *p1, float radius, unsigned int color, t_vec *p4);
t_object	cr_cone(t_vec *p1, float radius, unsigned int color, t_vec *p4);
t_object	cr_cylinder(t_vec *p1, float radius, unsigned int color, t_vec *p4);
t_object	cr_plane(t_vec *p1, t_vec *rot, unsigned int color);
t_vec	*cr_point(float i, float j, float k);

void fill_z_buffer(t_scene *scene);

// parser
t_vector	new_vec(double x, double y, double z);
int		camera(t_data *p, char **tab);
void	ambience(t_data *p, char *s);

// read
int		read_file(t_data *p, char *file);

// error
int		error_output(int error);
void 	scene_error(void);
int		error_handler(char *error);

// init
int		init(t_data *data);
int		init_figur(t_data *data, char *type, char *line);

// object
t_obj	*new_object(t_obj new);
t_obj	init_object(t_vector c, t_vector v, double a, double r);
t_obj	init_object_color(t_obj obj, double specular, char *color, int type);
int		create_object(t_data *data, char *line);
int		count_object(char *file);

// light
int			set_light(t_data *p, char **tab);
void		init_lights(t_data *p, char **s);
int			set_light(t_data *p, char **tab);
t_light		init_light(double x, double y, double z, double intens);
t_light		*new_light(t_light l);

// hook
int		escape(void);
int		key_press(int key, t_data *data);

// utils
void	free_tab(char **tab);
int		len_tab(char **tab);
void	check_tab_len(char **tab);
double	ft_strtodbl(char *s);
double	convert_to_rad(double a);
int		find_type(char *type);

// math

float	ft_vec_len(t_vec *vec);
float	find_cos(t_vec *vec1, t_vec *vec2);
float	find_cos2(int i1, int j1, int k1, int i2, int j2, int k2);
void	ft_normilize(t_vec *vec);
t_vec	*ft_vec_mult(t_vec *vec, float mult);
t_vec	*ftm_vec_mult(t_vec *vec, float mult);
t_vec	*ft_substr(t_vec *vec1, t_vec *vec2);
t_vec	*ft_add_vec(t_vec *vec1, t_vec *vec2);
t_vec	*ftm_add_vec(t_vec *vec1, t_vec *vec2);
float	ft_scal(t_vec *vec1, t_vec *vec2);
int		error_handler(char *error);

t_vec	*find_n_cyl(float t, t_vec *point, t_scene *scene, int index);
float	ray_intersect_cylinder(t_vec *dir, t_vec *point, t_object obj);
t_vec	*color_find_cylinder(t_vec *point, t_scene *scene, t_vec *sender, int k);
float	ray_intersect_pl(t_vec *dir, t_vec *point, t_object object);
t_vec 	*color_find_pl(t_vec *point, t_scene *scene, t_vec *sender, int k);
float	ray_intersect_cone(t_vec *dir, t_vec *point, t_object obj);
t_vec *find_cone_n(t_vec *point, t_scene *scene, t_vec *sender);
t_vec	*color_find_cone(t_vec *point, t_scene *scene, t_vec *sender, int k);
double	get_t(float a, float b, float d);
float sp_find_b(t_vec *point, t_vec *p1, t_vec *dir);
float sp_find_c(t_vec *point, t_vec *p1, float radius);
float	ray_intersect_sp(t_vec *dir, t_vec *point, t_object object);
t_vec *color_find_sp(t_vec *point, t_scene *scene, t_vec *sender, int k);


// rot

t_vec	vec_rot(t_vec dir, t_vec rot);
t_vec	rot_k(t_vec dir, double angle);
t_vec	rot_j(t_vec dir, double angle);
t_vec	rot_i(t_vec dir, double angle);


// col 
void ft_add_spec(t_vec *diffuse, float spec);
int ft_calc_res(t_scene *scene, int i, float NdotL, float spec);
float saturate(float d);
t_vec *point_coords(t_scene *scene, float t, t_vec *dir);
int ft_icol(t_vec *col);
t_vec *ft_split_col(int color);
int get_light(int start, int end, double percentage);
int get_col(float offset, unsigned int color);

// render
void render(t_scene *scene, t_mx *box);
void helper_for_render(int i, int j, t_scene *scene,  t_mx *box);
float cast_ray(t_vec *dir, t_scene *scene, unsigned int index);
t_vec *helper_for_casting(t_vec *sender, t_scene *scene, t_vec *dir, unsigned int index);
float calc_dist(t_vec *pos_light, t_vec *point);
int path_clear(t_vec *point, t_scene *scene, int i, int k);

#endif