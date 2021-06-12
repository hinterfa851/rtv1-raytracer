#include "includes/rtv1.h"

d_mlx *init_mlx(void)
{
    d_mlx *mlx_data;

    mlx_data = malloc(sizeof(d_mlx));
    mlx_data->connection_id = mlx_init();
    mlx_data->window_id = mlx_new_window(mlx_data->connection_id, 600, 600, "rt");
	mlx_data->image_id = mlx_new_image(mlx_data->connection_id, 600, 600);
	mlx_data->color_arr = mlx_get_data_addr(mlx_data->image_id, &mlx_data->bits_per_pixel, &mlx_data->size_line, &mlx_data->endian);	
    return (mlx_data);
}


int main(int argc, char **argv)
{
    d_mlx mlx_data;
    scene scene_obj;
 
    if (argc == 2)
	{
		if ((read_file(&mlx_data, &scene_obj, argv[1])) == -1)
			return (0);   
        render(&scene_obj, &mlx_data);
        printf("render done!\n");
        mlx_put_image_to_window(mlx_data.connection_id, mlx_data.window_id, mlx_data.image_id, 0, 0);
        mlx_loop(mlx_data.connection_id);
    }
    return (0);
}