#include "../includes/rtv1.h"

t_light	*new_light(t_light l)
{
	t_light	*light;

	light = (t_light*)malloc(sizeof(t_light));
	light->position.i = l.position.i;
	light->position.j = l.position.j;
	light->position.k = l.position.k;
	light->intensity = l.intensity;
	return (light);
}

t_light		init_light(double x, double y, double z, double intens)
{
	t_light	light;

	light.position.i = x;
	light.position.j = y;
	light.position.k = z;
//	printf("%f\t%f\t%f\n", light.x, light.y, light.z);
	light.intensity = intens;
	return (light);
}

void	init_lights(scene *scene_obj, char **s, int light_index)
{
	t_light		l;

	l = init_light(ft_strtodbl(s[0]), ft_strtodbl(s[1]),
			ft_strtodbl(s[2]), ft_strtodbl(s[3]));
//	printf("*%f\t%f\t%f*\n", new_l->x, new_l->y, new_l->z);
//	printf("%f\t%f\t%f\n", ((t_light *)(p->light)->content)->x, ((t_light *)(p->light)->content)->y, ((t_light *)(p->light)->content)->z);
	
	scene_obj->lights_array[light_index] = l;
}

int		set_light(scene *scene_obj, char **tab, int light_index)
{
	char	**str;

	str = ft_strsplit(tab[2], ',');
	if (len_tab(str) < 4)
	{
		free_tab(str);
		error_output(PARAMETERS);
		exit(0);
	}
	if (ft_strequ(tab[0], "light") && ft_strequ(tab[1], "point"))
		init_lights(scene_obj, str, light_index);
//	printf("%f\t%f\t%f\n", p->light->content, new_l->y, new_l->z);
//	printf("$%f\t%f\t%f\n", ((t_light *)(p->light)->content)->x, ((t_light *)(p->light)->content)->y, ((t_light *)(p->light)->content)->z);
	free_tab(str);
	return (0);
}
