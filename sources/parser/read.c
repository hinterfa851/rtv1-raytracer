/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:20:29 by glychest          #+#    #+#             */
/*   Updated: 2020/11/19 19:37:29 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		read_file(t_data *data, char *file)
{
	char	*line;

	data->obj_n = count_object(file);
	if (data->obj_n == -1)
		return (-1);
	data->figur = NULL;
	data->light = NULL;
	data->camera.cam = 0;
	if (!data->obj_n)
		return (error_output(NO_OBJECTS));
	if ((data->fd = open(file, O_RDONLY)) == -1)
		return (error_output(NO_FD));
	while ((get_next_line(data->fd, &line)) > 0)
	{
		create_object(data, line);
		free(line);
	}
	if (!data->camera.cam)
		return (error_output(NO_CAMERA));
	init(data);
	close(data->fd);
	return (0);
}
