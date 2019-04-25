/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:29:53 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/26 19:35:58 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	color_high(t_point *point, char *str)
{
	int		i;

	i = 2;
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) &&
			(str[i] < 65 || str[i] > 70) &&
			(str[i] < 97 || str[i] > 102))
			return (0);
		i++;
		if (i > 8)
			return (0);
	}
	if (i < 3)
		return (0);
	point->color = (int)strtol(str, NULL, 0);
	return (1);
}

int			search_color_nbr(t_fdf *fdf, t_point *point, char *str)
{
	char	*start_of_col;

	if ((start_of_col = ft_strchr(str, ',')))
	{
		*start_of_col = '\0';
		if (!validation_of_numbers(fdf, point, str))
			return (0);
		if (!color_high(point, start_of_col + 1))
		{
			alert_usage(2);
			return (0);
		}
		point->flag = 1;
	}
	else
	{
		if (!validation_of_numbers(fdf, point, str))
			return (0);
		point->flag = 0;
	}
	return (1);
}

int			digit_is(const char *str)
{
	if (*str == 45 || *str == 43)
		str++;
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (0);
		str++;
	}
	return (1);
}

int			validation_of_numbers(t_fdf *fdf, t_point *pnt, char *str)
{
	if (!digit_is(str))
	{
		alert_usage(3);
		return (0);
	}
	pnt->z = ft_atoi(str);
	if (pnt->z > fdf->max_z)
		fdf->max_z = pnt->z;
	if (pnt->z < fdf->min_z)
		fdf->min_z = pnt->z;
	return (1);
}

int			color_arg(t_fdf *fdf, char *str, int flag)
{
	int		i;

	i = 2;
	if (str[0] != '0' || str[1] != 'x')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] < 65 && str[i] > 70
			&& str[i] < 97 && str[i] > 102)
			return (0);
		i++;
	}
	if (i < 3 || i > 8)
		return (0);
	if (!flag)
	{
		fdf->max_color = (int)strtol(str, NULL, 0);
		fdf->min_color = fdf->max_color;
	}
	else
		fdf->min_color = (int)strtol(str, NULL, 0);
	fdf->flag = 1;
	return (1);
}
