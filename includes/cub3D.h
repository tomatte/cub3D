/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:19 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/01 09:54:34 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libs/libft/includes/libftprintf.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>

//screen
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 720

//keys
# define ESC_KEY 65307
# define ARROW_LEFT 65361
# define ARROW_UP 65362
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364

//colors
# define RED 0x00FF0000
# define DEFAULT_COLOR 0x000000FF
# define OCEAN 0x1D1776
# define LIME 0x00FF00

# define PI 3.1415926535

# define P_SIZE 8
# define TILE_SIZE 64
# define TOTAL_RAYS 60
# define VISION_ANGLE 45

typedef struct	s_player
{
	double	x;
	double	y;
	int		mv_up;
	int		mv_down;
	int		mv_left;
	int		mv_right;
	double	angle;
	double	mv_angle_r;
	double	mv_angle_l;
	double	delta_x;
	double	delta_y;
}	t_player;

typedef struct s_ray
{
	int		r;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	opx;
	double	opy;
	int		x_lower;
	double 	rate;
	double	rdx_row;
	double	rdy_row;
	double	rdx_col;
	double	rdy_col;
	double	column_x;
	double	column_y;
	double	row_y;
	double	row_x;
	double	is_base_x;
	double	angle;
	int		map_x;
	int		map_y;
}	t_ray;


typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	void		*texture_img;
	int			*texture_addr;
	int			texture_index;
	int			texture_width;
	int			texture_height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			color;
	t_player	player;
	t_ray		ray;
}	t_mlx;

typedef struct s_line
{
	int	x;
	int	y;
	int	x2;
	int	y2;
	int	w;
	int	h;
	int	dx1;
	int	dy1;
	int	dx2;
	int	dy2;
	int	longest;
	int	shortest;
	int	proportion;
	int	color;
}	t_line;

//minilibx
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y);
void	init_minilibx(t_mlx *mlx);
void	destroy_mlx(t_mlx *mlx);
void	put_image(t_mlx *mlx);
void	init__color(int *color);
void	set_color(int color);
int		get_color(void);

//line
void	asign_values(t_line *line);
void	draw_line(t_mlx *mlx, t_line line);
void	draw_line_textured(t_mlx *mlx, t_line line, int index);
t_line	points(int x, int y, int x2, int y2);

//hooks
void	init_hooks(t_mlx *mlx);
void	close_window_x(t_mlx *mlx);
void	move_hook(t_mlx *mlx);


//playground
void	square(t_mlx *mlx, int x, int y, int size);
void	square2(t_mlx *mlx, int x, int y, int size);
void	draw_player(t_mlx *mlx);
int		keep_drawing(t_mlx *mlx);
void	draw_2d_blocks(t_mlx *mlx, int size);

//move
void	update_player_position(t_mlx *mlx);

//tools
double	dmax(double a, double b);
double	positive(double num);
int		looking_up(double angle);
int		looking_left(double angle);
double	degrees_to_radians(double degrees);
double	normalize_angle(double angle);
double	round_base(double num, int base);
double	negative(double num);
int		has_floats(double num);
double	foward_square(double position);
double 	backward_square(double position);
void	rectangle(t_mlx *mlx, int x, int y, int size_x, int size_y);
void	draw_background(t_mlx *mlx);

#endif
