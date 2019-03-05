/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:17:41 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/05 18:33:51 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define BUFF_SIZE 1000
# define MAX_FD 1
# include "libft/includes/libft.h"
# include "fcntl.h"
# include "/usr/local/include/mlx.h"
# include "math.h"

typedef struct	s_3d
{
	double 		x;
	double 		y;
	double 		z;
}				t_3d;

typedef struct	s_2d
{
	double 		x;
	double 		y;
}				t_2d;

typedef struct	s_point
{
	int 		color;
	double 		x;
	double 		y;
	double 		z;
}				t_point;

typedef struct	s_fdf
{
	int			shift_x;
	int			shift_y;
	int			shift_z;
	void		*mlx_ptr;
	void		*win_ptr;
	double		ungle_x;
	double		ungle_y;
	double		ungle_z;
	int 		color;
	int 		count_of_words;
	int 		count_of_string;
	char		**map;
	double		factor;
	int			width;
	int			height;
	t_point     **pnts;
}				t_fdf;

int		get_next_line(const int fd, char **line);

#endif