/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:22:01 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/27 14:10:05 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void		initialization(t_fdf *fdf)
{
	fdf->min_z = 0;
	fdf->max_z = 0;
	fdf->cnt_of_str = 0;
	fdf->max_color = 0x0011ff;
	fdf->min_color = 0x039B0A;
	fdf->ungle_x = 0;
	fdf->ungle_y = 0;
	fdf->ungle_z = 0;
	fdf->width = 1920;
	fdf->height = 1080;
	fdf->shift_x = fdf->width / 2;
	fdf->shift_y = fdf->height / 2;
	fdf->shift_z = 0;
	fdf->factor = 20;
	fdf->flag = 0;
}

int				valid_ext(char *str)
{
	size_t		len;

	len = ft_strlen(str);
	if (len < 5 || str[len - 4] != '.' || str[len - 3] != 'f' ||
		str[len - 2] != 'd' || str[len - 1] != 'f')
	{
		alert_usage(1);
		return (0);
	}
	return (1);
}

static void		init_image(t_fdf fdf)
{
	fdf.mlx_ptr = mlx_init();
	fdf.img_pntr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.image_data = mlx_get_data_addr(fdf.img_pntr,
			&fdf.bpp, &fdf.sl, &fdf.endian);
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "FDF");
	mlx_hook(fdf.win_ptr, 2, 5, deal_key, &fdf);
	mlx_loop(fdf.mlx_ptr);
}

void			alert_usage(int error)
{
	if (!error)
		ft_putstr("usage: ./fdf map.fdf [[ 0x123456 ] [ 0x123456 ]] \n");
	if (error == 1)
		ft_putstr("\nExtension of file is not '.fdf' \n\nusage:"
			" ./fdf map.fdf [[ 0x123456 ] [ 0x123456 ]] \n");
	if (error == 2)
		ft_putstr("warning: invalid color \n");
	if (error == 3)
		ft_putstr("warning: invalid number \n");
	if (error == 4)
		ft_putstr("warning: invalid map \n");
	if (error == 5)
		ft_putstr("warning: file not found \n");
}

int				main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc < 5 && argc > 1)
	{
		initialization(&fdf);
		if (argc > 2 && argc < 5)
		{
			if (!color_arg(&fdf, argv[2], 0))
			{
				alert_usage(2);
				exit(0);
			}
			if (argc == 4 && !color_arg(&fdf, argv[3], 1))
			{
				alert_usage(2);
				exit(0);
			}
		}
		if (!for_2_arg(&fdf, argv[1]))
			return (0);
		init_image(fdf);
	}
	else
		alert_usage(0);
	return (0);
}
