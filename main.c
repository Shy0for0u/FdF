/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:22:01 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/05 18:51:45 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <string.h>

static void		rotation_y(t_fdf fdf, t_3d *point)
{
	double		x;
	double		z;
	double		y;

	y = point->y;
	x = point->x;
	z = point->z;
	point->x = x * cos(fdf.ungle_y) + z * sin(fdf.ungle_y);
	point->y = y;
	point->z = -x * sin(fdf.ungle_y) + z * cos(fdf.ungle_y);
}

static void		rotation_x(t_fdf fdf, t_3d *point)
{
	double		x;
	double		z;
	double		y;

	y = point->y;
	x = point->x;
	z = point->z;
	point->x = x;
	point->y = y * cos(fdf.ungle_x) + z * sin(fdf.ungle_x);
	point->z = -y * sin(fdf.ungle_x) + z * cos(fdf.ungle_x);
}

static void		rotation_z(t_fdf fdf, t_3d *point)
{
	double		x;
	double		z;
	double		y;

	y = point->y;
	x = point->x;
	z = point->z;
	point->z = z;
	point->x = x * cos(fdf.ungle_z) - y * sin(fdf.ungle_z);
	point->y = x * sin(fdf.ungle_z) + y * cos(fdf.ungle_z);
}

static int 		ft_max(int val1, int val2)
{
	return ((val1 > val2) ? val1 : val2);
}

static int 		get_L(int iXs, int iYs, int iXe, int iYe)
{
	int			iLx;
	int 		iLy;

	iLx = abs(iXe - iXs);
	iLy = abs(iYe - iYs);
	return (ft_max(iLx, iLy));
}

static t_2d		iso(t_fdf fdf, t_point pnt)
{
	t_2d	asd;
	t_3d	point;


	point.x = fdf.factor * pnt.x - (fdf.count_of_words * fdf.factor / 2);
	point.y = fdf.factor * pnt.y + fdf.shift_z - (fdf.count_of_string * fdf.factor / 2);
	point.z = fdf.factor * pnt.z + fdf.shift_z;

	rotation_z(fdf, &point);
	rotation_y(fdf, &point);
	rotation_x(fdf, &point);

	asd.x = ((point.x - point.y) * cos(0.523599)) + fdf.shift_x;
	asd.y = (-point.z + (point.x + point.y) * sin(0.523599)) + fdf.shift_y;
	return (asd);
}

static void		DDL(t_fdf fdf, t_2d pnt1, t_2d pnt2)
{
	double	X;
	double	Y;
	int 	L;
	double	dX;
	double 	dY;

	X = pnt1.x + 0.5;
	Y = pnt1.y + 0.5;
	L = get_L((int)floor(X), (int)floor(Y), (int)floor(pnt2.x + 0.5), (int)floor(pnt2.y + 0.5));
	dX = (pnt2.x - pnt1.x) / L;
	dY = (pnt2.y - pnt1.y) / L;
	while (L--)
	{
		X += dX;
		Y += dY;
		if (X <= fdf.width && Y <= fdf.height)
		{
			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, (int)X, (int)Y, fdf.color);
		}
	}
}

static void		regular_works(t_fdf *fdf)
{
	t_2d		start;
	t_2d		end;
	int 		i;
	int 		j;

	i = 0;
	while (i < fdf->count_of_string)
	{
		j = 0;
		while (j < fdf->count_of_words)
		{
			start = iso(*fdf, fdf->pnts[i][j]);
			fdf->color = fdf->pnts[i][j].color;
			if (j + 1 < fdf->count_of_words)
			{
				end = iso(*fdf, fdf->pnts[i][j + 1]);
				DDL(*fdf, start, end);
			}
			if (i + 1 < fdf->count_of_string)
			{
				end = iso(*fdf, fdf->pnts[i + 1][j]);
				DDL(*fdf, start, end);
			}
			j++;
		}
		i++;
	}
}

static void		offset(t_fdf *fdf, int key)
{
	if (key == 124) // right
		fdf->shift_x += 10;
	if (key == 123) // left
		fdf->shift_x -= 10;
	if (key == 126) // up
		fdf->shift_y -= 10;
	if (key == 125) // down
		fdf->shift_y += 10;
	if (key == 78) // +
		fdf->shift_z += 10;
	if (key == 69) // -
		fdf->shift_z -= 10;
}

static int				do_it_shit(int key, t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if (key == 53)
		exit(0);
	if (key == 7) // X
		fdf->ungle_x += 0.05;
	if (key == 1) // S
		fdf->ungle_x -= 0.05;
	if (key == 8) // C
		fdf->ungle_y += 0.05;
	if (key == 2) // D
		fdf->ungle_y -= 0.05;
	if (key == 6) // Z
		fdf->ungle_z += 0.05;
	if (key == 0) // A
		fdf->ungle_z -= 0.05;
	if (key == 12) // Q
		fdf->factor += 1;
	if (key == 13 && fdf->factor > 0) // W
		fdf->factor -= 1;
	offset(fdf, key);
	regular_works(fdf);
	return (0);
}

static int		cnt_words(char const *str, char c)
{
	int			cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
		{
			cnt++;
		}
		str++;
	}
	return (cnt);
}

static int 		ft_counting(t_fdf *fdf, char *name)
{
	char 		*line;
	int			fd;

	fdf->count_of_string = 0;
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (fdf->count_of_string == 0)
		{
			fdf->count_of_words = cnt_words(line, ' ');
			fdf->count_of_string++;
			ft_strdel(&line);
			continue ;
		}
		if (fdf->count_of_words != cnt_words(line, ' '))
			return (0);
		fdf->count_of_string++;
		ft_strdel(&line);
	}
	close(fd);
	return (1);
}

int 		read_map2(t_fdf *fdf, const char *str)
{
	int 	fd;
	int 	i;

	i = 0;
	fd = open(str, O_RDONLY);
	while ((get_next_line(fd, &fdf->map[i])))
	{
		i++;
	}
	close(fd);
	return (1);
}

static int		hex2int(const char *nbr, int len)
{
	int 		i;
	int			val;

	i = 0;
	val = 0;
	while (i < len)
	{
		if (nbr[i] <= 57)
			val += (nbr[i] - 48) * (1 << (4 * (len - 1 - i)));
		else
			val += (nbr[i] - 55) * (1 << (4 * (len - 1 - i)));
		i++;
	}
	return (val);
}

static int		color_arg(t_fdf *fdf, char *str)
{
	int			i;

	i = 2;
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] < 65 && str[i] > 70
			&& str[i] < 97 && str[i] > 102)
			return (0);
		i++;
		if (i > 8)
			return (0);
	}
	fdf->color = hex2int((str + 2), 6);
	return (1);
}

static int		color_high(t_point *point, char *str)
{
	int			i;

	i = 2;
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] < 65 && str[i] > 70
		&& str[i] < 97 && str[i] > 102)
			return (0);
		i++;
		if (i > 8)
			return (0);
	}
	point->color = hex2int(str + 2, 6);
	return (1);
}

static int		validation_of_numbers(t_point *point, char *str)
{
	int 		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	point->z = ft_atoi(str);
	return (1);
}

static int		search_color_nbr(t_fdf *fdf, t_point *point, char *str)
{
	char	*start_of_col;

	if ((start_of_col = ft_strchr(str, ',')))
	{
		*start_of_col = '\0';
		if (!validation_of_numbers(point, str))
			return (0);
		if (!color_high(point, start_of_col + 1))
			return (0);
	}
	else
	{
		if (!validation_of_numbers(point, str))
			return (0);
		point->color = fdf->color;
	}
	return (1);
}

static int	create_map(t_fdf *fdf)
{
	int		i;
	int 	j;
	char 	**array;

	i = 0;
	if (!(fdf->pnts = (t_point**)malloc(sizeof(t_point*) * fdf->count_of_string)))
		return (0);
	while (i != fdf->count_of_string)
	{
		if (!(fdf->pnts[i] = (t_point*)malloc(sizeof(t_point) * fdf->count_of_words)))
			return (0);
		j = 0;
		array = ft_strsplit(fdf->map[i], ' ');
		while (array[j])
		{
			fdf->pnts[i][j].x = j;
			fdf->pnts[i][j].y = i;
			if (!search_color_nbr(fdf, &fdf->pnts[i][j], array[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	initialization(t_fdf *fdf)
{
	fdf->color = (0xFFFFFF >> 16) & 0xFF;
	fdf->ungle_x = 0;
	fdf->ungle_y = 0;
	fdf->ungle_z = 0;
	fdf->width = 1500;
	fdf->height = 1000;
	fdf->shift_x = fdf->width / 2;
	fdf->shift_y = fdf->height / 2;
	fdf->shift_z = 0;
	fdf->factor = 20;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->width, fdf->height, "FDF");
}

static int	for_2_arg(t_fdf *fdf, char *str)
{
	if (!ft_counting(fdf, str))
		return (0);
	if (!(fdf->map = (char**)malloc(sizeof(char*) * fdf->count_of_string)))
		return (0);
	if (!read_map2(fdf, str))
		return (0);
	if (!create_map(fdf))
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_fdf fdf;

	if (argc <= 3 || argc != 1)
	{
		initialization(&fdf);
		if (argc == 3)
		{
			if (!color_arg(&fdf, argv[2]))
				exit(0);
		}
		if (!for_2_arg(&fdf, argv[1]))
			return (0);
		mlx_hook(fdf.win_ptr, 2, 5, do_it_shit, &fdf);
		mlx_loop(fdf.mlx_ptr);
	}
	return (0);
}