/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:23:47 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/26 18:43:20 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void		type_of_projection(t_fdf *fdf, int key)
{
	if (key == 3 && fdf->type)
	{
		fdf->ungle_x = 0;
		fdf->ungle_y = 0;
		fdf->ungle_z = 0;
		fdf->type = 0;
	}
	else if (key == 3)
	{
		fdf->ungle_x = 0;
		fdf->ungle_y = 0;
		fdf->ungle_z = 0;
		fdf->type = 1;
	}
}

static void		spin(t_fdf *fdf, int key)
{
	if (key == 7)
		fdf->ungle_x += 0.08;
	if (key == 1)
		fdf->ungle_x -= 0.08;
	if (key == 8)
		fdf->ungle_y += 0.08;
	if (key == 2)
		fdf->ungle_y -= 0.08;
	if (key == 6)
		fdf->ungle_z += 0.08;
	if (key == 0)
		fdf->ungle_z -= 0.08;
}

static void		offset(t_fdf *fdf, int key)
{
	if (key == 124)
		fdf->shift_x += 20;
	if (key == 123)
		fdf->shift_x -= 20;
	if (key == 126)
		fdf->shift_y -= 20;
	if (key == 125)
		fdf->shift_y += 20;
	if (key == 78)
		fdf->shift_z += 20;
	if (key == 69)
		fdf->shift_z -= 20;
}

int				deal_key(int key, t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->img_pntr = mlx_new_image(fdf->mlx_ptr, fdf->width, fdf->height);
	fdf->image_data = mlx_get_data_addr(fdf->img_pntr,
			&fdf->bpp, &fdf->sl, &fdf->endian);
	if (key == 53)
	{
		delete_structure(fdf);
		exit(0);
	}
	type_of_projection(fdf, key);
	spin(fdf, key);
	if (key == 12)
		fdf->factor += 1;
	if (key == 13 && fdf->factor > 0)
		fdf->factor -= 1;
	offset(fdf, key);
	regular_works(fdf);
	return (0);
}
