/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:01:03 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/18 14:48:17 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static double	percent(int start, int end, int current)
{
	double		placement;
	double		distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int		get_light(int start, int end, double rate)
{
	return ((int)((1 - rate) * start + rate * end));
}

int				get_color(t_2d current, t_2d pnt1, t_2d pnt2)
{
	int			red;
	int			green;
	int			blue;
	double		rate;

	if (current.color == pnt2.color)
		return (current.color);
	if ((pnt2.x - pnt1.x) > (pnt2.y - pnt1.y))
		rate = percent((int)pnt1.x, (int)pnt2.x, (int)current.x);
	else
		rate = percent((int)pnt1.y, (int)pnt2.y, (int)current.y);
	red = get_light((pnt1.color >> 16) & 0xFF, (pnt2.color >> 16) & 0xFF, rate);
	green = get_light((pnt1.color >> 8) & 0xFF, (pnt2.color >> 8) & 0xFF, rate);
	blue = get_light(pnt1.color & 0xFF, pnt2.color & 0xFF, rate);
	return ((red << 16) | (green << 8) | blue);
}

int				z_color(t_fdf fdf, double z)
{
	int			red;
	int			green;
	int			blue;
	double		rate;

	if (z == fdf.min_z)
		return (fdf.min_color);
	if (z == fdf.max_z)
		return (fdf.max_color);
	rate = percent((int)fdf.max_z, (int)fdf.min_z, (int)z);
	red = get_light((fdf.min_color >> 16) & 0xFF,
			(fdf.max_color >> 16) & 0xFF, rate);
	green = get_light((fdf.min_color >> 8) & 0xFF,
			(fdf.max_color >> 8) & 0xFF, rate);
	blue = get_light(fdf.min_color & 0xFF, fdf.max_color & 0xFF, rate);
	return ((red << 16) | (green << 8) | blue);
}
