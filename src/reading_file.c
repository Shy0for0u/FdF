/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:08:15 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/27 14:20:11 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	rm_foo(t_fdf *fdf, int y, char *line)
{
	int		x;
	char	**array;

	x = 0;
	array = ft_strsplit(line, ' ');
	if (!(fdf->pnts[y] = (t_point*)malloc(sizeof(t_point) * fdf->words)))
		return (0);
	while (x < fdf->words)
	{
		fdf->pnts[y][x].x = x;
		fdf->pnts[y][x].y = y;
		if (!search_color_nbr(fdf, &fdf->pnts[y][x], array[x]))
			return (0);
		if (!fdf->pnts[y][x].flag)
			fdf->pnts[y][x].color = z_color(*fdf, fdf->pnts[y][x].z);
		x++;
	}
	del_array(array);
	return (1);
}

static int	read_map(t_fdf *fdf, const char *str)
{
	int		fd;
	int		y;
	char	*line;

	y = 0;
	line = NULL;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (!rm_foo(fdf, y, line))
		{
			ft_strdel(&line);
			return (0);
		}
		y++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (1);
}

static int	counting_words(char const *str, char c)
{
	int		cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
			cnt++;
		str++;
	}
	return (cnt);
}

static int	ft_counting(t_fdf *fdf, char *name)
{
	char	*line;
	int		fd;
	char	buff[1];

	line = NULL;
	fd = open(name, O_RDONLY);
	if (read(fd, buff, 0) < 0 || fd < 0)
	{
		return (5);
	}
	while (get_next_line(fd, &line))
	{
		if (fdf->cnt_of_str == 0)
			fdf->words = counting_words(line, ' ');
		if (fdf->words != counting_words(line, ' '))
			return (4);
		fdf->cnt_of_str++;
		ft_strdel(&line);
	}
	if (fdf->cnt_of_str == 0)
		return (4);
	ft_strdel(&line);
	close(fd);
	return (1);
}

int			for_2_arg(t_fdf *fdf, char *str)
{
	int		alert;

	if (!valid_ext(str))
		return (0);
	alert = ft_counting(fdf, str);
	if (alert == 4)
	{
		alert_usage(4);
		return (0);
	}
	else if (alert == 5)
	{
		alert_usage(5);
		return (0);
	}
	if (!(fdf->pnts = (t_point**)malloc(sizeof(t_point*) * fdf->cnt_of_str)))
		return (0);
	if (!read_map(fdf, str))
		return (0);
	return (1);
}
