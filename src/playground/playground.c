/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/10 13:59:38 by dbrandao         ###   ########.fr       */
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

static void	draw_rays(t_mlx *mlx)
{
	t_player	*p;
	t_ray		*r;
	int			i;
	int			aux;

	p = &mlx->player;
	r = &mlx->ray;
	set_color(0x0);
	draw_line(mlx, points(r->opx, r->opy, r->x, r->y));
	r->x = p->x * cos(p->angle) * 50;
	r->y = p->y * sin(p->angle) * 50;
	set_color(RED);
	aux = 0;
	i = 0;
	while (i++ < 2)
	{
		if (p->angle < PI)
		{
			aux = r->y + 63 - (int) r->y % 63;
			if (aux <= SCREEN_HEIGHT)
				r->y = aux;
		}
		else
		{
			aux = r->y - (int) (r->y) % 63;
			if (aux >= 0)
				r->y = aux;
		}
		if (p->angle > PI / 2 && p->angle < PI + PI / 2)
		{
			aux = r->x - (int) (r->x) % 63;
			if (aux >= 0)
				r->x = aux;
		}
		else
		{
			aux = r->x + 63 - (int) (r->x) % 63;
			if (aux <= SCREEN_WIDTH)
				r->x = aux;
		}
	}
	r->opx = p->x + P_SIZE / 2;
	r->opy = p->y + P_SIZE / 2;
	draw_line(mlx, points(p->x + P_SIZE / 2, p->y + P_SIZE / 2, r->x, r->y));
	set_color(DEFAULT_COLOR);
}

/*

	rate =  min(cos, sin) / max(cos, sin)

	x_greater = cos(a) > sin(a);
	rate = min(cos(a), sin(a)) / max(cos(a), sin(a);
	if (x_greater)
	{
		r->x += 63 - (int) (r->x) % 63;
		r->y = r->x * rate;
	}
	else
	{
		r->y += 63 - (int) (r->y) % 63;
		r->x = r->y * rate;
	}

 */

int	looking_up(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (p->angle > PI)
	{
		return (1);
	}
	return (0);
}

int	looking_left(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (p->angle > PI / 2 && p->angle < PI + PI / 2)
	{
		return (1);
	}
	return (0);
}

double	get_rate(double angle)
{
	double	rate;

	rate = cos(angle) / sin(angle);
	return (rate);
}

double	get_ray_dx(t_mlx *mlx)
{
	t_ray		*r;
	double		dx;

	r = &mlx->ray;
	if (looking_left(mlx))
		dx = (int) round(r->x) % 63;
	else
		dx = 63 - (int) round(r->x) % 63;
	if (dx == 0)
		dx = 63;
	return (dx);
}

double	get_ray_dy(t_mlx *mlx)
{
	t_ray		*r;
	double		dy;

	r = &mlx->ray;
	if (looking_up(mlx))
		dy = (int) round(r->y) % 63;
	else
		dy = 63 - (int) round(r->y) % 63;
	if (dy == 0)
		dy = 63;
	return (dy);
}

static double	positive(double num)
{
	if (num < 0)
		return (-num);
	return (num);
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

double	dmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

void	test_case(t_mlx *mlx)
{
	t_player	*p;
	t_ray		*r;
	int			i = 0;
	double		rdx1;
	double		rdy1;
	double		rdx2;
	double		rdy2;
	double		old_x;
	double		old_y;

	p = &mlx->player;
	r = &mlx->ray;
	r->x = p->x;
	r->y = p->y;
	while (i++ < 20)
	{
		//base y or lines
		rdy1 = get_ray_dy(mlx);
		rdx1 = rdy1 * (cos(p->angle) / sin(p->angle));

		//base x or columns
		rdx2 = get_ray_dx(mlx);
		rdy2 = rdx2 * (sin(p->angle) / cos(p->angle));
		if (dmax(rdy1, rdx1) > dmax(rdy2, rdx2))
			jump_next_column(mlx);
		else
			jump_next_line(mlx);
		//jump_next_column(mlx);
		if (r->x > SCREEN_WIDTH || r->y > SCREEN_HEIGHT || r->x < 0 || r->y < 0)
			break ;
		square2(mlx, (int) round(r->x), (int) round(r->y), P_SIZE);
	}
}

static void	erase_player(t_mlx *mlx)
{
	set_color(0x0);
	draw_player(mlx);
	test_case(mlx);
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	erase_player(mlx);
	update_player_position(mlx);
	draw_2d_blocks(mlx, 64);
	draw_player(mlx);
	test_case(mlx);
	//draw_rays(mlx);
	put_image(mlx);
	return (1);
}
