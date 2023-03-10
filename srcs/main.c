/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:44:31 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/10 19:15:47 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	display_help_message(void)
{
	ft_putstr_fd("Usage:\n", 1);
	ft_putstr_fd("$>./fractol \"mandelbrot\"         ", 1);
	ft_putstr_fd("| displays the mandelbrot fractal\n", 1);
	ft_putstr_fd("$>./fractol \"burningship\"        ", 1);
	ft_putstr_fd("| displays the burningship fractal\n", 1);
	ft_putstr_fd("$>./fractol \"julia\" \"-0.6\" \"0.4\" ", 1);
	ft_putstr_fd("| displays the given julia fractal, default to \"0\" \"0\"\n", 1);
}

static int	fractol(int argc, char **argv)
{
	t_state	state;

	init_state(&state);
	if (parse_and_set(argc, argv, &state))
	{
		display_help_message();
		return (1);
	}
	if (init_mlx(&state))
	{
		ft_putstr_fd("error: failed to initialize mlx\n", 1);
		return (1);
	}
	init_mlx_hooks(&state);
	mlx_loop(state.mlx_ptr);
	free_mlx(&state);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		display_help_message();
		return (0);
	}
	return (fractol(argc, argv));
}
