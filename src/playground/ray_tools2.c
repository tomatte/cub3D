/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:13:58 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 22:20:18 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	foward_square(double position)
{
	double	result;

	result = (((int) position >> 6) << 6) + 64.000000 - 0.99999999;
	return (result);
}

double	backward_square(double position)
{
	double	result;

	result = (((int) position >> 6) << 6) - 0.00000001;
	return (result);
}

double	get_ray_distance(t_mlx *mlx)
{
	t_ray		*r;
	t_player	*p;
	double		h;
	double		ca;

	r = &mlx->ray;
	p = &mlx->player;
	h = sqrt(pow(positive(r->x - p->x), 2) + pow(positive(r->y - p->y), 2));
	ca = normalize_angle(positive(r->angle - mlx->player.angle));
	return (h * cos(ca));
}

double	get_rdy(double rdx, double angle)
{
	double	rdy;

	if (angle == PI / 2 || angle == PI + PI / 2)
		return (0);
	rdy = rdx * tan(angle);
	if (looking_up(angle))
		return (negative(rdy));
	return (positive(rdy));
}

double	get_rdx(double rdy, double angle)
{
	double	rdx;

	if (angle == 0 || angle == PI)
		return (0);
	rdx = rdy * (1 / tan(angle));
	if (looking_left(angle))
		return (negative(rdx));
	return (positive(rdx));
}
