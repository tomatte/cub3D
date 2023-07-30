/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/30 15:13:01 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	draw_direction_line(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	draw_line(
		mlx,
		points(
			round(p->x + P_SIZE / 2),
			round(p->y + P_SIZE / 2),
			round(p->x + (P_SIZE / 2) + (p->delta_x * 20)),
			round(p->y + (P_SIZE / 2) + (p->delta_y * 20))
			)
		);
}

void	draw_player(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	square2(mlx, (int) round(p->x), (int) round(p->y), P_SIZE);
	draw_direction_line(mlx);
}

const int map[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

double	get_rdy(double rdx, double angle)
{
	double	rd_rate;
	double	rdy;

	if (angle == PI / 2 || angle == PI + PI / 2)
		return (0);
	rd_rate = positive(cos(angle) / sin(angle));
	rdy = rdx / rd_rate;
	if (looking_up(angle))
		return (negative(rdy));
	return (positive(rdy));
}

double	get_rdx(double rdy, double angle)
{
	double	rd_rate;
	double	rdx;

	if (angle == 0 || angle == PI)
		return (0);
	rd_rate = positive(sin(angle) / cos(angle));
	rdx = rdy / rd_rate;
	if (looking_left(angle))
		return (negative(rdx));
	return (positive(rdx));
}

void	calc_next_column_values(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (looking_left(r->angle))
		r->column_x = backward_square(r->x);
	else
		r->column_x = foward_square(r->x);
	r->rdx_col = r->column_x - r->x;
	r->rdy_col = get_rdy(r->rdx_col, r->angle);
	r->column_y = r->y + r->rdy_col;
}

void	calc_next_row_values(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (looking_up(r->angle))
		r->row_y = backward_square(r->y);
	else
		r->row_y = foward_square(r->y);
	r->rdy_row = r->row_y - r->y;
	r->rdx_row = get_rdx(r->rdy_row, r->angle);
	r->row_x = r->x + r->rdx_row;
}

void	jump_to_next_square(t_mlx *mlx)
{
	t_ray	*r;
	int		old_x;
	int		old_y;
	double	dox;
	double	doy;

	r = &mlx->ray;
	dox = r->x;
	doy = r->y;
	old_x = (int) round(r->x);
	old_y = (int) round(r->y);
	if (positive(r->rdx_col) + positive(r->rdy_col) <
		positive(r->rdx_row) + positive(r->rdy_row) ||
		r->rdy_col == 0)
	{
		r->x  = r->column_x;
		r->y  = r->column_y;
	}
	else
	{
		r->x  = r->row_x;
		r->y  = r->row_y;
	}
	draw_line(mlx, points(old_x, old_y, (int) round(r->x), (int) round(r->y)));
	if (r->x >= TILE_SIZE * 15 || r->y >= TILE_SIZE * 11 - 30)
	{
		printf("dox: %lf | doy: %lf  |  (intxy)[%d|%d]\n", dox, doy, (int) dox, (int) doy);
	}
}

/* 	printf("x: %lf |  backward: %lf  |  forward: %lf \n", p->x, backward_square(p->x), foward_square(p->x));
	printf("y: %lf |  backward: %lf  |  forward: %lf \n", p->y, backward_square(p->y), foward_square(p->y));
	printf("x: %lf | y: %lf  |  map[%d][%d] == %d\n", mlx->ray.x, mlx->ray.y, mlx->ray.map_x, mlx->ray.map_y, map[mlx->ray.map_x][mlx->ray.map_y]);
	*/

int	is_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		x;
	int		y;

	r = &mlx->ray;
	if (looking_left(r->angle))
		x = (int) (r->x / TILE_SIZE);
	else
		x = (int) (ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int) (r->y / TILE_SIZE);
	else
		y = (int) (ceil(r->y) / TILE_SIZE);
	return (map[y][x]);
}

void	dda_ray(t_mlx *mlx)
{
	int			i = 0;

	mlx->ray.x = mlx->player.x + P_SIZE / 2;
	mlx->ray.y = mlx->player.y + P_SIZE / 2;
	//mlx->ray.angle = mlx->player.angle;
	mlx->ray.map_x = (int) (mlx->ray.x / TILE_SIZE);
	mlx->ray.map_y = (int) (mlx->ray.y / TILE_SIZE);
	while (i++ < 16)
	{
		calc_next_column_values(mlx);
		calc_next_row_values(mlx);
		jump_to_next_square(mlx);
		if (is_wall(mlx))
			break ;
		//printf("(%d) map_x: %d | map_y: %d  |  map_return: %d\n", i, mlx->ray.map_x, mlx->ray.map_y, );
		if (mlx->ray.map_x < 0 || mlx->ray.map_x > 14 || mlx->ray.map_y < 0 || mlx->ray.map_y > 10)
			break ;
	}
}

static void	multiple_rays(t_mlx *mlx)
{
	double	ray_mod;
	double	sum;
	double	vision_angle;
	double	limit_angle;
	t_player	*p;
	t_ray		*r;

	p = &mlx->player;
	r = &mlx->ray;
	vision_angle = degrees_to_radians(40);
	ray_mod = vision_angle / 40;
	limit_angle = vision_angle / 2;
	sum = limit_angle * -1;
	while (sum < limit_angle)
	{
		r->angle = normalize_angle(p->angle + sum);
		dda_ray(mlx);
		sum += ray_mod;
	}
}

static void	eraser(t_mlx *mlx)
{
	set_color(0x0);
	draw_player(mlx);
	multiple_rays(mlx);
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	eraser(mlx);
	update_player_position(mlx);
	draw_2d_blocks(mlx, TILE_SIZE);
	draw_player(mlx);
	set_color(RED);
	multiple_rays(mlx);
	set_color(DEFAULT_COLOR);
	put_image(mlx);
	return (1);
}
