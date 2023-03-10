/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:49:08 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/10 18:56:54 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_mlx(t_state *state)
{
	if (state->win_ptr)
		mlx_destroy_window(state->mlx_ptr, state->win_ptr);
	if (state->img.mlx_img)
		mlx_destroy_image(state->mlx_ptr, state->img.mlx_img);
	if (state->mlx_ptr)
	{
		mlx_destroy_display(state->mlx_ptr);
		free(state->mlx_ptr);
	}
}

void	init_state(t_state *state)
{
	state->mlx_ptr = NULL;
	state->win_ptr = NULL;
	state->img.mlx_img = NULL;
	state->img.addr = NULL;
	state->roi.center.x = 0;
	state->roi.center.y = 0;
	state->roi.h = 4.0;
	state->roi.w = 4.0;
	state->max_iter = ITER_START;
	state->julia_c.i = 0.0;
	state->julia_c.r = 0.0;
}

int	init_mlx(t_state *state)
{
	state->mlx_ptr = mlx_init();
	if (!state->mlx_ptr)
		return (MLX_ERROR);
	state->win_ptr = mlx_new_window(state->mlx_ptr, RES_W, RES_H, "fractol");
	if (!state->win_ptr)
	{
		free_mlx(state);
		return (MLX_ERROR);
	}
	state->img.mlx_img = mlx_new_image(state->mlx_ptr, RES_W, RES_H);
	if ((!state->img.mlx_img))
	{
		free_mlx(state);
		return (MLX_ERROR);
	}
	state->img.addr = mlx_get_data_addr(state->img.mlx_img, &(state->img.bpp),
			&(state->img.line_len), &(state->img.endian));
	if (!(state->img.addr))
	{
		free_mlx(state);
		return (MLX_ERROR);
	}
	return (0);
}

void	init_mlx_hooks(t_state *state)
{
	mlx_hook(state->win_ptr, KeyPress, KeyPressMask, &handle_keypress, state);
	mlx_hook(state->win_ptr, 17, 1L << 17, mlx_loop_end, state->mlx_ptr);
	mlx_mouse_hook(state->win_ptr, &handle_mouse, state);
	mlx_expose_hook(state->win_ptr, &render, state);
}

int	parse_and_set(int argc, char **argv, t_state *state)
{
	if (!ft_strncmp(argv[1], MANDELBROT, MAX_INPUT_LEN))
	{
		state->set = mandelbrot;
		return (0);
	}
	if (!ft_strncmp(argv[1], JULIA, MAX_INPUT_LEN))
	{
		state->set = julia;
		if (argc > 2)
			state->julia_c.r = ft_atof(argv[2]);
		if (argc > 3)
			state->julia_c.i = ft_atof(argv[3]);
		return (0);
	}
	if (!ft_strncmp(argv[1], BURNINGSHIP, MAX_INPUT_LEN))
	{
		state->set = burningship;
		return (0);
	}
	return (1);
}
