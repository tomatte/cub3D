/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:19 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/10 14:49:18 by suzy             ###   ########.fr       */
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
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 920

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
# define TOTAL_RAYS 81
# define VISION_ANGLE 40

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

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

typedef struct s_texture
{
	void		*img;
	int			*addr;
	int			width;
	int			height;
	int			line;
	int			direction_code;
	int			***colors;
	int		is_inversed;
	double	vertical_proportion;
	double	horizontal_proportion;
	double	tile_map_x;
	double	tile_map_y;
}	t_texture;

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
	double	old_x;
	double	old_y;
	double	line_length;
	int		line_mod;
	double	line_begin;
	double	line_end;
	double	vertial_proportion;
	double	distance;
	double	horizontal_proportion;
	double	tile_map_x;
	double	tile_map_y;
	int		is_texture_inversed;
	int		map_x;
	int		map_y;
}	t_ray;


typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	t_texture	texture;
	void		*texture_img;
	int			*texture_addr;
	int			texture_width;
	int			texture_height;
	int			texture_line;
	int			ray_index_w;
	int			***texture_colors;
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
void	dda_ray(t_mlx *mlx);
void	multiple_rays(t_mlx *mlx);

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
double	get_ray_distance(t_mlx *mlx);
double	get_rdy(double rdx, double angle);
double	get_rdx(double rdy, double angle);

#endif
