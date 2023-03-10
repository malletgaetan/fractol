/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:44:43 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/10 18:56:40 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	iterate(t_complex *z, t_complex *c, int max_iter)
{
	double	x2;
	double	y2;
	double	tmp;
	int		i;

	i = 0;
	x2 = z->r * z->r;
	y2 = z->i * z->i;
	while ((x2 + y2 <= 4.0) && (i < max_iter))
	{
		tmp = z->r;
		z->r = x2 - y2 + c->r;
		z->i = (2 * z->i * tmp) + c->i;
		x2 = z->r * z->r;
		y2 = z->i * z->i;
		++i;
	}
	return (i);
}

int	mandelbrot(t_state *state, t_complex *coord)
{
	t_complex	z;

	z.r = 0;
	z.i = 0;
	return (iterate(&z, coord, state->max_iter));
}

int	julia(t_state *state, t_complex *coord)
{
	t_complex	z;

	z.i = coord->i;
	z.r = coord->r;
	return (iterate(&z, &(state->julia_c), state->max_iter));
}

int	burningship(t_state *state, t_complex *coord)
{
	t_complex	z;
	double		x2;
	double		y2;
	double		tmp;
	int			i;

	i = 0;
	x2 = 0;
	y2 = 0;
	z.r = 0;
	z.i = 0;
	while ((x2 + y2 <= 4.0) && (i < state->max_iter))
	{
		tmp = z.r;
		z.r = x2 - y2 + coord->r;
		z.i = fabs(2 * z.i * tmp) + coord->i;
		x2 = z.r * z.r;
		y2 = z.i * z.i;
		++i;
	}
	return (i);
}
