/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:43:34 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/02 14:43:29 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	dmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	positive(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	looking_up(double angle)
{
	if (angle > PI)
		return (1);
	return (0);
}

int	looking_left(double angle)
{
	if (angle > PI / 2 && angle < PI + PI / 2)
		return (1);
	return (0);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
}

double	round_base(double num, int base)
{
	double	result;

	result = round(num / (double) base) * base;
	return (result);
}

double	negative(double num)
{
	if (num > 0)
		return (num * -1);
	return (num);
}

int	has_floats(double num)
{
	if (num - (int) num != 0)
		return (1);
	return (0);
}

double	foward_square(double position)
{
	double	result;

	result = position + (TILE_SIZE - (int) round(position) % TILE_SIZE);
	return (round_base(result, TILE_SIZE));
}

double	backward_square(double position)
{
	double	result;

	result = position - ((int) round(position) % TILE_SIZE);
	return (round_base(result, TILE_SIZE) - 1);
}

double	get_ray_distance(t_mlx *mlx)
{
	t_ray		*r;
	t_player	*p;
	double		h;

	r = &mlx->ray;
	p = &mlx->player;
	h = sqrt(pow(positive(r->x - p->x), 2) + pow(positive(r->y - p->y), 2));
	return (h);
}

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
