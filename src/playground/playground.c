/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/20 12:51:23 by dbrandao         ###   ########.fr       */
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

double	round_base(double num, int base)
{
	double	result;

	result =  round( num / (double) base) * base;
	return result;
}



double	negative(double num)
{
	if (num > 0)
		return (num * -1);
	return (num);
}

double	get_rdy(double rdx, double angle)
{
	double	rd_rate;
	double	rdy;

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

	rd_rate = positive(sin(angle) / cos(angle));
	rdx = rdy / rd_rate;
	if (looking_left(angle))
		return (negative(rdx));
	return (positive(rdx));
}

/*
	//printf("Angle: %lf\nX: %lf  |  x/y: %lf\nY: %lf  |  y/x: %lf\n", p->angle, r->x, positive(cos(p->angle)/sin(p->angle)), r->y, positive(sin(p->angle)/cos(p->angle)));
	//printf("next_column: %lf  |  rdx: %lf\n", new_rx, rdx);
	//printf("rx + rdx: %lf\n", r->x + rdx);
 */

void	next_column(t_mlx *mlx)
{
	t_ray	*r;
	t_player	*p;
	double	rd_rate;
	double	rdx;

	r = &mlx->ray;
	p = &mlx->player;
	if (looking_left(p->angle))
	{
		rdx = ((int) r->x % TILE_SIZE) * -1;
		if (rdx == 0)
			rdx = -TILE_SIZE;
	}
	else
		rdx = (TILE_SIZE - ((int) r->x % TILE_SIZE));
	r->rdx_col = rdx;
	r->column_x = round_base(r->x + rdx, TILE_SIZE);
	r->rdy_col = get_rdy(rdx, p->angle);
}

void	next_line(t_mlx *mlx)
{
	t_ray	*r;
	t_player	*p;
	double	rd_rate;
	double	rdy;

	r = &mlx->ray;
	p = &mlx->player;
	if (looking_up(p->angle))
	{
		rdy = ((int) r->y % TILE_SIZE) * -1;
		if (rdy == 0)
			rdy = -TILE_SIZE;
	}
	else
		rdy = (TILE_SIZE - ((int) r->y % TILE_SIZE));
	r->rdy_line = rdy;
	r->line_y = round_base(r->y + rdy, TILE_SIZE);
	r->rdx_line = get_rdx(rdy, p->angle);
}

void	calc_next_point(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	next_line(mlx);
	next_column(mlx);
	if (dmax(positive(r->rdx_col), positive(r->rdy_col)) <
		dmax(positive(r->rdx_line), positive(r->rdy_line)))
	{
		r->x = r->column_x;
		r->y += get_rdy(r->rdx_col, mlx->player.angle);
	}
	else
	{
		r->y = r->line_y;
		r->x += get_rdx(r->rdy_line, mlx->player.angle);
	}
}

void	dda_ray(t_mlx *mlx)
{
	t_player	*p;
	t_ray		*r;
	int			i = 0;
	int			color;

	double		old_x;
	double		old_y;

	p = &mlx->player;
	r = &mlx->ray;
	r->x = p->x + 4;
	r->y = p->y + 4;
	old_x = r->x;
	old_y = r->y;
	while (i++ < 13)
	{
		calc_next_point(mlx);
		draw_line(mlx, points(round(old_x), round(old_y), round(r->x), round(r->y)));
	}
}

static void	multiple_rays(t_mlx *mlx)
{
	double	save_angle;
	double	ray_mod;
	double	sum;
	double	vision_angle;
	double	limit_angle;

	save_angle = mlx->player.angle;
	vision_angle = degrees_to_radians(40);
	ray_mod = vision_angle / 40;
	limit_angle = vision_angle / 2;
	sum = limit_angle * -1;
	while (sum < limit_angle)
	{
		mlx->player.angle = normalize_angle(save_angle + sum);
		dda_ray(mlx);
		sum += ray_mod;
	}
	mlx->player.angle = save_angle;
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
	draw_2d_blocks(mlx, 64);
	draw_player(mlx);
	set_color(RED);
	multiple_rays(mlx);
	set_color(DEFAULT_COLOR);
	put_image(mlx);
	return (1);
}
