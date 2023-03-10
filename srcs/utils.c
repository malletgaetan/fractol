/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:44:58 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/10 19:13:02 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	rgb(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

int	hsv_to_rgb(double h, double s, double v)
{
	double	c;
	double	m;
	double	x;

	c = v * s;
	x = c * (1.0 - fabs(fmod(h / 60.0, 2) - 1.0));
	m = v - c;
	if (h >= 0.0 && h < 60.0)
		return (rgb((int)(c + m), (int)(x + m), (int)m));
	if (h >= 60.0 && h < 120.0)
		return (rgb((int)(x + m), (int)(c + m), (int)m));
	if (h >= 120.0 && h < 180.0)
		return (rgb((int)(m), (int)(c + m), (int)(x + m)));
	if (h >= 180.0 && h < 240.0)
		return (rgb((int)(m), (int)(x + m), (int)(c + m)));
	if (h >= 240.0 && h < 300.0)
		return (rgb((int)(x + m), (int)(m), (int)(c + m)));
	if (h >= 300.0 && h < 360.0)
		return (rgb((int)(c + m), (int)(m), (int)(x + m)));
	return (rgb((int)(m), (int)(m), (int)m));
}

double	ft_atof(char *str)
{
	double	nb;
	double	scale;
	double	sign;

	nb = 0;
	scale = 0.1;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		nb = (nb * 10) + (*(str++) - '0');
	if (*str != '.')
		return (sign * nb);
	while (ft_isdigit(*(++str)))
	{
		nb += (*str - '0') * scale;
		scale = scale / 10;
	}
	return (sign * nb);
}
