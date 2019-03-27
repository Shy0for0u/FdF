/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:17:41 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/25 10:34:47 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define BUFF_SIZE 77
# define MAX_FD 1
# include "../libft/includes/libft.h"
# include "fcntl.h"
# include "/usr/local/include/mlx.h"
# include "math.h"
# include <string.h>
# include <stdatomic.h>

typedef struct	s_3d
{
	double		x;
	double		y;
	double		z;
}				t_3d;

typedef struct	s_2d
{
	double		x;
	double		y;
	int			color;

}				t_2d;

typedef struct	s_point
{
	int			flag;
	int			color;
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct	s_fdf
{
	int			type;
	void		*img_pntr;
	char		*image_data;
	int			bpp;
	int			sl;
	int			endian;
	int			shift_x;
	int			shift_y;
	int			shift_z;
	void		*mlx_ptr;
	void		*win_ptr;
	double		ungle_x;
	double		ungle_y;
	double		ungle_z;
	int			max_color;
	int			min_color;
	int			words;
	int			cnt_of_str;
	double		factor;
	int			width;
	int			height;
	t_point		**pnts;
	double		max_z;
	double		min_z;
	int			flag;
}				t_fdf;
int				get_next_line(int fd, char **line);
int				for_2_arg(t_fdf *fdf, char *str);
void			del_array(char **array);
int				search_color_nbr(t_fdf *fdf, t_point *point, char *str);
int				validation_of_numbers(t_fdf *fdf, t_point *point, char *str);
int				color_arg(t_fdf *fdf, char *str, int flag);
int				deal_key(int key, t_fdf *fdf);
void			regular_works(t_fdf *fdf);
void			dda(t_fdf fdf, t_2d pnt1, t_2d pnt2);
t_2d			iso(t_fdf fdf, t_point pnt);
void			delete_structure(t_fdf *fdf);
int				get_color(t_2d current, t_2d pnt1, t_2d pnt2);
int				z_color(t_fdf fdf, double z);
void			alert_usage(int error);
int				valid_ext(char *str);
#endif
