/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:19:04 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/22 12:00:50 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		del_array(char **array)
{
	int		i;

	i = 0;
	if (array != NULL)
	{
		while (array[i])
		{
			ft_strdel(&array[i]);
			i++;
		}
		free(array);
	}
}

void		delete_structure(t_fdf *fdf)
{
	int		i;

	i = 0;
	while (i < fdf->cnt_of_str)
	{
		free(fdf->pnts[i]);
		i++;
	}
	free(fdf->pnts);
}

static void	foo(t_fdf *fdf, int i, int j)
{
	t_2d	start;
	t_2d	end;

	start = iso(*fdf, fdf->pnts[i][j]);
	if (j + 1 < fdf->words)
	{
		end = iso(*fdf, fdf->pnts[i][j + 1]);
		dda(*fdf, start, end);
	}
	if (i + 1 < fdf->cnt_of_str)
	{
		end = iso(*fdf, fdf->pnts[i + 1][j]);
		dda(*fdf, start, end);
	}
}

void		regular_works(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->cnt_of_str)
	{
		j = 0;
		while (j < fdf->words)
		{
			foo(fdf, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_pntr, 0, 0);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img_pntr);
}
