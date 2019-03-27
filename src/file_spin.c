/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_spin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:32:48 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/25 10:35:54 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

t_2d			iso(t_fdf fdf, t_point pnt)
{
	t_2d		asd;
	t_3d		point;

	asd.color = pnt.color;
	point.x = fdf.factor * pnt.x - (fdf.words - 1) * fdf.factor / 2;
	point.y = fdf.factor * pnt.y + fdf.shift_z -
			(fdf.cnt_of_str - 1) * fdf.factor / 2;
	point.z = fdf.factor * pnt.z + fdf.shift_z -
			(fdf.max_z - fdf.min_z) * fdf.factor / 2;
	if (fdf.type)
	{
		rotation_z(fdf, &point);
		asd.x = ((point.x - point.y) * cos(0.523599)) + fdf.shift_x;
		asd.y = (-point.z + (point.x + point.y) * sin(0.523599)) + fdf.shift_y;
	}
	else
	{
		rotation_z(fdf, &point);
		rotation_y(fdf, &point);
		rotation_x(fdf, &point);
		asd.y = point.y + fdf.shift_y;
		asd.x = (point.x) + fdf.shift_x;
	}
	return (asd);
}
