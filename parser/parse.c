#include "../includes/rtv1.h"

int		create_camera(scene *p, char **tab)
{
	char	**str;

	str = NULL;
	str = ft_strsplit(tab[1], ',');
	if (len_tab(str) < 6)
	{
		free_tab(str);
		error_output(PARAMETERS);
		exit(-1);
	}
	p->camera.position.i = ft_atoi(str[0]);
	p->camera.position.j = ft_atoi(str[1]);
	p->camera.position.k = ft_atoi(str[2]);
	p->camera.rotation.i = ft_strtodbl(str[3]);
	p->camera.rotation.j = ft_strtodbl(str[4]);
	p->camera.rotation.k = ft_strtodbl(str[5]);
	free_tab(str);
	return (0);
}

void	ambience(scene *p, char *s)
{
	p->ambient = ft_strtodbl(s);
	// if (p->ambient > 1)
	// 	p->ambient = 1;
}

// t_vector	new_vec(double x, double y, double z)
// {
// 	t_vector vec;

// 	vec.x = x;
// 	vec.y = y;
// 	vec.z = z;
// 	return (vec);
// }
