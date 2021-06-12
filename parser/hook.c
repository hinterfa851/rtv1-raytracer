
#include "../includes/rtv1.h"

int		escape(void)
{
	exit(1);
	return (0);
}

int		key_press(int key, d_mlx *data)			// + scene ?? free?
{
	data = NULL;
	if (key == 53)
		exit(escape());
	return (0);
}
