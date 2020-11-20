/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:46:34 by glychest          #+#    #+#             */
/*   Updated: 2020/11/19 19:35:36 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		escape(void)
{
	exit(1);
	return (0);
}

int		key_press(int key, t_data *data)
{
	data = NULL;
	if (key == 53)
		exit(escape());
	return (0);
}
