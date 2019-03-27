/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:24:08 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/26 18:55:08 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int		ft_max(int val1, int val2)
{
	return ((val1 > val2) ? val1 : val2);
}

static int		get_l(int ixs, int iys, int ixe, int iye)
{
	int			ilx;
	int			ily;

	ilx = abs(ixe - ixs);
	ily = abs(iye - iys);
	return (ft_max(ilx, ily));
}

static int		check_edge(t_fdf fdf, int x, int y)
{
	if (x > (fdf.width - 1) || x < 1)
		return (0);
	if (y > (fdf.height - 1) || y < 1)
		return (0);
	return (1);
}

static void		write_index(t_fdf *fdf, int index, t_2d cur)
{
	fdf->image_data[index] = (char)(cur.color >> 16 & 0xFF);
	fdf->image_data[index + 1] = (char)(cur.color >> 8 & 0xFF);
	fdf->image_data[index + 2] = (char)(cur.color & 0xFF);
}

void			dda(t_fdf fdf, t_2d pnt1, t_2d pnt2)
{
	int			l;
	double		dx;
	double		dy;
	t_2d		current;
	int			index;

	current.x = pnt1.x + 0.5;
	current.y = pnt1.y + 0.5;
	l = get_l((int)floor(current.x), (int)floor(current.y),
			(int)floor(pnt2.x + 0.5), (int)floor(pnt2.y + 0.5));
	dx = ((pnt2.x - pnt1.x) / l);
	dy = ((pnt2.y - pnt1.y) / l);
	while (l--)
	{
		current.x += dx;
		current.y += dy;
		index = (int)(current.x) * 4 + fdf.sl * (int)current.y;
		current.color = get_color(current, pnt1, pnt2);
		if (check_edge(fdf, (int)current.x, (int)current.y))
			write_index(&fdf, index, current);
	}
}
