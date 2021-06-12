#include "../includes/rtv1.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

void check_tab_len(char **tab)
{
	if (len_tab(tab) != 2)
	{
		free_tab(tab);
		error_output(INVALID);
		exit(-1);
	}
}

double ft_strtodbl(char *s)
{
	char **tab;
	vector n;
	int i;
	int len;
	int dot;

	n.i = 0.0;
	i = 0;
	n.j = 0;
	dot = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '.')
			dot++;
		i++;
	}
	if (!dot)
		return ((double)ft_atoi(s));
	tab = ft_strsplit(s, '.');
	check_tab_len(tab);
	n.i = (double)ft_atoi(tab[0]);
	n.j = (double)ft_atoi(tab[1]);
	len = ft_strlen(tab[1]);
	while (--len > -1)
		n.j /= 10;
	n.i += n.j;
	free_tab(tab);
	return (n.i);
}

int find_type(char *type)
{
	int t;

	t = 0;
	if (ft_strequ(type, "sphere"))
		t = SPHERE;
	else if (ft_strequ(type, "cone"))
		t = CONE;
	else if (ft_strequ(type, "cylinder"))
		t = CYLINDER;
	else if (ft_strequ(type, "plane"))
		t = PLANE;
	return (t);
}

double convert_to_rad(double a)
{
	while (a > 360.0)
		a -= 360.0;
	while (a < 0.0)
		a += 360.0;
	a = (a * PI) / 360.0;
	return (a);
}
