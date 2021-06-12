#include "../includes/rtv1.h"

void fill_z_buffer(scene *scene)
{
    int i;

    i = 0;
    scene->z_buffer = malloc(WIN_SIZE_X * WIN_SIZE_Y * sizeof(float));
    while(i < WIN_SIZE_X * WIN_SIZE_Y)
        scene->z_buffer[i++] = MAXDISTANCE;
}

void initialize_arrays(scene *scene)
{
	scene->objects_array = malloc(sizeof(object) * scene->obj_count);
	scene->lights_array = malloc(sizeof(t_light) * scene->light_count);
	fill_z_buffer(scene);
}


int		read_file(d_mlx *init_mlx, scene *scene, char *file)
{
	int		fd;
	char	*line;

	scene->obj_count = count_object(file);
	scene->light_count = count_lights(file);
	if ((scene->obj_count < 1) || (scene->light_count < 1))
		return (-1);
	scene->camera.count = 0;
	if (!scene->obj_count)
		return (error_output(NO_OBJECTS));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_output(NO_FD));
	initialize_arrays(scene);
	while ((get_next_line(fd, &line)) > 0)
	{
		create_object(scene, line);
		free(line);
	}
	if (!scene->camera.count)
		return (error_output(NO_CAMERA));
	init(init_mlx);
	close(fd);
	return (0);
}
