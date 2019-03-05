/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:16:12 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/11 13:19:58 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putchar(char c)
{
	int	tmp1;
	int	tmp2;

	if ((unsigned char)c < 128)
		write(1, &c, 1);
	else
	{
		tmp1 = 192 + (int)c / 64;
		tmp2 = 128 + (int)c % 64;
		write(1, &tmp1, 1);
		write(1, &tmp2, 1);
	}
}
