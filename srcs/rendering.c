/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42lehavre.fr >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:19:06 by gmallet           #+#    #+#             */
/*   Updated: 2023/06/13 13:19:07 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	render_line(t_state *state, t_render *param)
{
	int		x;
	int		iter;

	x = 0;
	while (x < RES_W)
	{
		iter = state->set(state, &(param->c));
		img_pix_put(&(state->img), x, param->y,
			hsv_to_rgb(iter % 256, 255, 255 * (iter < state->max_iter)));
		++x;
		param->c.r += param->wi;
	}
}

static void	render_set(t_state *state)
{
	t_render	param;
	double		hi;
	double		r_start;

	param.y = 0;
	param.wi = state->roi.w / RES_W;
	param.c.i = state->roi.center.y - (state->roi.h / 2);
	r_start = state->roi.center.x - (state->roi.w / 2);
	hi = state->roi.h / RES_H;
	while (param.y < RES_W)
	{
		param.c.r = r_start;
		render_line(state, &param);
		param.c.i += hi;
		++param.y;
	}
}

int	render(t_state *state)
{
	render_set(state);
	mlx_put_image_to_window(state->mlx_ptr, state->win_ptr,
		state->img.mlx_img, 0, 0);
	return (0);
}
