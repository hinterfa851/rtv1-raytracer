#include "../includes/rtv1.h"

object	*new_object(object new)
{
	object	*obj;

	obj = (object*)malloc(sizeof(object));
	obj->position = new.position;
	obj->rotation = new.rotation;
	obj->radius = new.radius;
//	obj->specular = new.specular;
	obj->color = new.color;
	obj->type = new.type;
	return (obj);
}

void add_functions_to_object(object *figure)
{
	if (figure->type == 1)
	{
		figure->ray_intersect = ray_intersect_sp;
		figure->find_normal = find_normal_sphere;
	}
	else if (figure->type == 2)
	{
		figure->ray_intersect = ray_intersect_cylinder;
		figure->find_normal = find_normal_cylinder;
	}
	else if (figure->type == 3)
	{
		figure->ray_intersect = ray_intersect_cone;
		figure->find_normal = find_normal_cone;
	}
	else
	{
		figure->ray_intersect = ray_intersect_pl;
		figure->find_normal = find_normal_plane;
	}
}

object	init_object_color(object *obj, double specular, char *color, int type) // ?? spec??
{
//	obj.specular = specular;
	printf("init color i, j, k - %f\t%f\t%f\n", obj->rotation->i, obj->rotation->j, obj->rotation->k);
	if (ft_strequ(color, "red"))
		obj->color = RED;
	else if (ft_strequ(color, "green"))
		obj->color = GREEN;
	else if (ft_strequ(color, "blue"))
		obj->color = BLUE;
	else
		obj->color = 249710846;
	obj->type = type;
	add_functions_to_object(obj);
	return (*obj);
}

object	*init_object(vector c, vector v, double a, double r)
{
	object	*obj;
	vector	*default_rotation;
	vector	result_rotation;

	obj = malloc(sizeof(object));
	default_rotation = cr_point(0, 1, 0);
	obj->position = malloc(sizeof(vector));
	obj->rotation = malloc(sizeof(vector));
	result_rotation = rotate_vector(*default_rotation, v);
	
	obj->rotation->i = result_rotation.i;
	obj->rotation->j = result_rotation.j;
	obj->rotation->k = result_rotation.k; 
	
	obj->position->i = c.i;
	obj->position->j = c.j;
	obj->position->k = c.k;

	obj->radius = r;
	obj->refletcion = a;
	return (obj);
}

int		create_object(scene *scene_obj, char *line)
{
	static int light_count;
	static int object_count;
	char	**tab;
	int		ret;

	tab = NULL;
	ret = 0;
	tab = ft_strsplit(line, ' ');
	if (ft_strequ(tab[0], "sphere") || ft_strequ(tab[0], "cylinder") ||
	ft_strequ(tab[0], "cone") || ft_strequ(tab[0], "plane"))
	{
		ret = init_figur(scene_obj, tab[0], tab[1], object_count++);
//		printf("i, j, k - %f\t%f\t%f\n", scene_obj->objects_array[0].rotation->i, scene_obj->objects_array[0].rotation->j, scene_obj->objects_array[0].rotation->k);
		if (ret == -1)
			return (-1);
	}
	if (ft_strequ(tab[0], "camera"))
	{
		scene_obj->camera.count++;
		if ((create_camera(scene_obj, tab)) == -1)
			exit(0);
	}
	if (ft_strequ(tab[0], "light"))
		set_light(scene_obj, tab, light_count++);
	// if (ft_strequ(tab[0], "ambient"))
	// 	ambience(scene_obj, tab[1]);
	free_tab(tab);
	return (0);
}


int		count_object(char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_output(NO_FD));
	while ((get_next_line(fd, &line)) > 0)
	{
		if ((ft_strncmp(line, "sphere", 6)) == 0 ||
		(ft_strncmp(line, "cylinder", 8)) == 0 ||
		(ft_strncmp(line, "cone", 4)) == 0 ||
		(ft_strncmp(line, "plane", 5)) == 0)
			i++;
		free(line);
	}
	close(fd);
	return (i);
}

int		count_lights(char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_output(NO_FD));
	while ((get_next_line(fd, &line)) > 0)
	{
		if ((ft_strncmp(line, "light", 5)) == 0)
			i++;
		free(line);
	}
	close(fd);
	return (i);
}