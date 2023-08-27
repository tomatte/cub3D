/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:14:08 by suzy              #+#    #+#             */
/*   Updated: 2023/08/27 17:50:32 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	get_distance(double old_x, double old_y, double x, double y)
{
	double	h;

	h = sqrt(pow(positive(x - old_x), 2) + pow(positive(y - old_y), 2));
	return (h);
}

double	fish_eye_fix(t_mlx *mlx, double h)
{
	double	ca;

	ca = normalize_angle(positive(mlx->ray.angle - mlx->player.angle));
	return (h * cos(ca));
}

int	is_limit2(double x, double y)
{
	if (x < 0)
		return (1);
	if (y < 0)
		return (1);
	return (0);
}

void	choose_axis(t_mlx *mlx)
{
	t_ray		*r;
	t_player	*p;
	double		h_dist;
	double		v_dist;

	r = &mlx->ray;
	p = &mlx->player;
	h_dist = get_distance(p->x, p->y, r->horizontal_x, r->horizontal_y);
	v_dist = get_distance(p->x, p->y, r->vertical_x, r->vertical_y);
	if (h_dist < v_dist)
	{
		r->x = r->horizontal_x;
		r->y = r->horizontal_y;
		r->is_vertical = 0;
	}
	else
	{
		r->x = r->vertical_x;
		r->y = r->vertical_y;
		r->is_vertical = 1;
	}
}

void	dda_ray(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	r->horizontal_x = mlx->player.x;
	r->horizontal_y = mlx->player.y;
	r->vertical_x = mlx->player.x;
	r->vertical_y = mlx->player.y;
	find_vertical_wall(mlx);
	find_horizontal_wall(mlx);
	choose_axis(mlx);
}
