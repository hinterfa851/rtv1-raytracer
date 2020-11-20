/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:26:31 by glychest          #+#    #+#             */
/*   Updated: 2020/11/19 19:35:12 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		error_output(int error)
{
	if (error == USAGE)
		ft_putendl("Usage: ./rtv1 <scene>");
	if (error == NO_CAMERA)
		ft_putendl("File is invalid: no camera");
	if (error == NO_OBJECTS)
		ft_putendl("File is invalid: no objects");
	if (error == NO_FD)
		ft_putendl("Error: cannot open file");
	if (error == PARAMETERS)
		ft_putendl("Object is invalid: wrong number of parameters");
	if (error == INVALID)
		ft_putendl("Invalid parameter");
	return (-1);
}

void	scene_error(void)
{
	ft_putendl("Incorect scene");
	exit(0);
}
