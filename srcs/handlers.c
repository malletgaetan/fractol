/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:44:28 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/10 18:44:28 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_in(t_state *state, int x, int y)
{
	double	vec_x;
	double	vec_y;

	vec_x = ((double)x - (double)(RES_W / 2)) * (state->roi.w / RES_W);
	vec_y = ((double)y - (double)(RES_H / 2)) * (state->roi.h / RES_H);
	state->roi.center.x += vec_x * ZOOM_MOVE_POWER;
	state->roi.center.y += vec_y * ZOOM_MOVE_POWER;
	state->roi.h = state->roi.h / ZOOM_POWER;
	state->roi.w = state->roi.w / ZOOM_POWER;
	state->max_iter += ITER_INC;
}

static void	zoom_out(t_state *state, int x, int y)
{
	double	vec_x;
	double	vec_y;

	vec_x = ((double)x - (double)(RES_W / 2)) * (state->roi.w / RES_W);
	vec_y = ((double)y - (double)(RES_H / 2)) * (state->roi.h / RES_H);
	state->roi.center.x -= vec_x * ZOOM_MOVE_POWER;
	state->roi.center.y -= vec_y * ZOOM_MOVE_POWER;
	state->roi.h = state->roi.h * ZOOM_POWER;
	state->roi.w = state->roi.w * ZOOM_POWER;
	state->max_iter -= ITER_INC;
}

int	handle_mouse(int mousecode, int x, int y, t_state *state)
{
	if (mousecode == 4)
		zoom_in(state, x, y);
	else if (mousecode == 5)
		zoom_out(state, x, y);
	else if (mousecode == 1)
	{
		state->julia_c.i = ((state->roi.h / RES_H) * y) - (state->roi.h / 2);
		state->julia_c.r = ((state->roi.w / RES_W) * x) - (state->roi.w / 2);
	}
	else
		return (0);
	render(state);
	return (0);
}

int	handle_keypress(int keysym, t_state *state)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(state->mlx_ptr);
		return (0);
	}
	if (keysym == XK_Left)
		state->roi.center.x -= MOVE_POWER * state->roi.w;
	else if (keysym == XK_Right)
		state->roi.center.x += MOVE_POWER * state->roi.w;
	else if (keysym == XK_Up)
		state->roi.center.y -= MOVE_POWER * state->roi.h;
	else if (keysym == XK_Down)
		state->roi.center.y += MOVE_POWER * state->roi.h;
	else if (keysym == XK_r)
	{
		state->roi.center.x = 0;
		state->roi.center.y = 0;
		state->roi.h = 4.0;
		state->roi.w = 4.0;
	}
	else
		return (0);
	render(state);
	return (0);
}
