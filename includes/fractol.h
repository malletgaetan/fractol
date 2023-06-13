/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:44:22 by gmallet           #+#    #+#             */
/*   Updated: 2023/03/10 19:12:35 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define RES_W 600
# define RES_H 600
# define MLX_ERROR 1
# define ALLOC_ERROR 2
# define ITER_START 100
# define ITER_INC 5
# define ZOOM_POWER 1.5
# define ZOOM_MOVE_POWER 0.5
# define MOVE_POWER 0.2
# define MAX_INPUT_LEN 11
# define MANDELBROT "mandelbrot"
# define JULIA "julia"
# define BURNINGSHIP "burningship"

# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_complex
{
	double	i;
	double	r;
}	t_complex;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_roi
{
	t_point	center;
	double	w;
	double	h;
}	t_roi;

typedef struct s_render
{
	int			y;
	double		wi;
	t_complex	c;
}	t_render;

typedef struct s_state
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			max_iter;
	t_img		img;
	t_roi		roi;
	int			cur_img;
	t_complex	julia_c;
	int			(*set)(struct s_state *state, t_complex *coord);
}	t_state;

void	free_mlx(t_state *state);
void	init_state(t_state *state);
int		init_mlx(t_state *state);
void	init_mlx_hooks(t_state *state);
int		parse_and_set(int argc, char **argv, t_state *state);
int		handle_keypress(int keysym, t_state *state);
int		handle_mouse(int mousecode, int x, int y, t_state *state);
int		mandelbrot(t_state *state, t_complex *c);
int		julia(t_state *state, t_complex *c);
int		burningship(t_state *state, t_complex *c);
int		render(t_state *state);
int		hsv_to_rgb(double h, double s, double v);
double	ft_atof(char *str);

#endif