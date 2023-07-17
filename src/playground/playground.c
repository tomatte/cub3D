/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/17 16:45:11 by dbrandao         ###   ########.fr       */
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

double	get_ray_dx(t_mlx *mlx)
{
	t_ray		*r;
	double		dx;

	r = &mlx->ray;
	if (looking_left(mlx))
		dx = positive(remainder(r->x, 63.0));
	else
		dx = 63.0 - positive(remainder(r->x, 63));
	if (dx == 0)
		dx = 63.0;
	return (dx);
}

double	get_ray_dy(t_mlx *mlx)
{
	t_ray		*r;
	double		dy;

	r = &mlx->ray;
	if (looking_up(mlx))
		dy = positive(remainder(r->y, 63.0));
	else
		dy = 63 - positive(remainder(r->y, 63.0));
	if (dy == 0)
		dy = 63;
	return (dy);
}

void	jump_next_column(t_mlx *mlx)
{
	t_ray		*r;
	t_player	*p;
	double		rdx;
	double		rdy;

	r = &mlx->ray;
	p = &mlx->player;
	rdx = get_ray_dx(mlx);
	rdy = rdx * (sin(p->angle) / cos(p->angle));
	if (rdy > 63 || rdx > 63)
		return ;
	if (looking_left(mlx))
		r->x -= rdx;
	else
		r->x += rdx;
	if (looking_up(mlx))
		r->y -= positive(rdy);
	else
		r->y += positive(rdy);
}

void	jump_next_line(t_mlx *mlx)
{
	t_ray		*r;
	t_player	*p;
	double		rdx;
	double		rdy;

	r = &mlx->ray;
	p = &mlx->player;
	rdy = get_ray_dy(mlx);
	rdx = rdy * (cos(p->angle) / sin(p->angle));
	if (rdy > 63 || rdx > 63)
		return ;
	if (looking_up(mlx))
		r->y -= rdy;
	else
		r->y += rdy;
	if (looking_left(mlx))
		r->x -= positive(rdx);
	else
		r->x += positive(rdx);
}

int	column_nearest(t_mlx *mlx)
{
	double		rdx1;
	double		rdy1;
	double		rdx2;
	double		rdy2;
	double		angle;

	angle = mlx->player.angle;
	//base y or lines
	rdy1 = get_ray_dy(mlx);
	rdx1 = rdy1 * (cos(angle) / sin(angle));

	//base x or columns
	rdx2 = get_ray_dx(mlx);
	rdy2 = rdx2 * (sin(angle) / cos(angle));
	if (dmax(rdy1, positive(rdx1)) > dmax(positive(rdy2), rdx2))
		return (1);
	return (0);
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

//arredondar um dos eixos para o bloco mais proximo
int	is_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		map_column;
	int		map_line;

	r = &mlx->ray;

	return (1);
}

void debug(t_mlx *mlx)
{
	t_ray	*r;
	int	map_column;
	int	map_line;

	r = &mlx->ray;
	if (looking_left(mlx))
		map_column = (int) (r->x / 63.0);
	else
		map_column = (int) (r->x / 63.0);
	if (looking_up(mlx))
		map_line = (int) (r->y / 63.0);
	else
		map_line = (int) (r->y / 63.0);
	//printf("line: %d  | column: %d  |  rx: %lf : %lf |  ry: %lf : %lf  |  wall: %d\n", map_line, map_column, r->x, r->x / 63.0, r->y, r->y / 63.0, map[map_line][map_column]);
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
	while (i++ < 3)
	{
		old_x = r->x;
		old_y = r->y;
		if (column_nearest(mlx))
			jump_next_column(mlx);
		else
			jump_next_line(mlx);
		if (r->x > SCREEN_WIDTH || r->y > SCREEN_HEIGHT || r->x < 0 || r->y < 0)
			break ;
		draw_line(mlx, points((int) round(old_x), (int) round(old_y), (int) round(r->x), (int) round(r->y)));
		if (is_wall(mlx) && get_color())
		{
			color = get_color();
			set_color(LIME);
			square(mlx, (int) round(r->x), (int) round(r->y), 2);
			set_color(color);
		}
	}
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
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
