/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:12:54 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/20 16:05:42 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	search_n(char **array, char **line)
{
	char	*ptr;
	char	**ptr_array;

	if ((ptr = ft_strchr(*array, '\n')))
	{
		ptr_array = &ptr;
		if (!(*line = ft_strsub(*array, 0, ptr - *array)))
		{
			ft_strdel(ptr_array);
			ft_strdel(array);
			return (-1);
		}
		*array = ft_strcpy(*array, (ptr + 1));
	}
	else
	{
		if (!(*line = ft_strdup(*array)))
		{
			ft_strdel(array);
			return (-1);
		}
		ft_strdel(array);
	}
	return (1);
}

static int	create_string(char *buff, char **array)
{
	char	*ptr;

	if (*array)
	{
		ptr = *array;
		if (!(*array = ft_strjoin(*array, buff)))
		{
			ft_strdel(&ptr);
			return (0);
		}
		ft_strdel(&ptr);
	}
	else
	{
		if (!(*array = ft_strdup(buff)))
			return (0);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*array[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	long		ret;

	if (fd < 0 || read(fd, buff, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (!create_string(buff, &array[fd]))
			return (-1);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if ((array[fd]) == NULL || array[fd][0] == '\0')
		return (0);
	return (search_n(&array[fd], line));
}
