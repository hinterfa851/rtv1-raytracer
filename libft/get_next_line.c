/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glychest <glychest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:51:58 by glychest          #+#    #+#             */
/*   Updated: 2020/11/15 15:56:33 by glychest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# define BUFF_SIZE 32
# define MAX_FD 12288

static int		line_end(char **str, char **line)
{
	int				len;
	char			*tmp;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_strsub(*str, 0, len);
		tmp = ft_strdup(&((*str)[len + 1]));
		free(*str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

static int		output(char **str, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	if (str[fd] == NULL)
		return (0);
	else
		return (line_end(&str[fd], line));
}

int				get_next_line(const int fd, char **line)
{
	static char		*str[MAX_FD];
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if (fd < 0 || line == NULL || fd > MAX_FD)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str[fd], buff);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	return (output(str, line, ret, fd));
}
