/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:14:08 by suzy              #+#    #+#             */
/*   Updated: 2023/08/26 14:14:24 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

int	is_limit(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	if (r->x <= 0 || r->y <= 0)
		return (1);
	if (r->x >= SCREEN_WIDTH || r->y >= SCREEN_HEIGHT)
		return (1);
	return (0);
}

int	is_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		x;
	int		y;

	r = &mlx->ray;
	if (looking_left(r->angle))
		x = (int)(r->x / TILE_SIZE);
	else
		x = (int)(ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int)(r->y / TILE_SIZE);
	else
		y = (int)(ceil(r->y) / TILE_SIZE);
	if (x < 0 || x > 15 || y < 0 || y > 15)
		return (0);
	if (map[y][x] == 1)
	{
		r->map_x = x;
		r->map_y = y;
	}
	return (map[y][x]);
}

int	is_wall2(double rx, double ry, double angle)
{
	int		x;
	int		y;

	if (looking_left(angle))
		x = (int)(rx / TILE_SIZE);
	else
		x = (int)(ceil(rx) / TILE_SIZE);
	if (looking_up(angle))
		y = (int)(ry / TILE_SIZE);
	else
		y = (int)(ceil(ry) / TILE_SIZE);
	if (x < 0 || x > 15 || y < 0 || y > 15)
		return (-1);
	return (map[y][x]);
}

double	get_distance(double old_x, double old_y, double x, double y, t_mlx *mlx)
{
	double	h;
	double	ca;

	h = sqrt(pow(positive(x - old_x), 2) + pow(positive(y - old_y), 2));
	ca = normalize_angle(positive(mlx->ray.angle - mlx->player.angle));
	return (h * cos(ca));
}

int	is_limit2(double x, double y)
{
	if (x < 0 || x > SCREEN_WIDTH)
		return (1);
	if (y < 0 || y > SCREEN_HEIGHT)
		return (1);
	return (0);
}

void	first_vertical_side(t_mlx *mlx)
{
	t_ray	*r;
	double	rdy;

	r = &mlx->ray;
	if (looking_left(r->angle))
		r->vertical_x = backward_square(r->vertical_x);
	else
		r->vertical_x = foward_square(r->vertical_x);
	rdy = get_rdy(positive(r->vertical_x - mlx->player.x), r->angle);
	r->vertical_y += rdy;
}

void	vertical_offset(t_mlx *mlx, double *xo, double *yo)
{
	t_ray	*r;

	r = &mlx->ray;
	if (looking_left(r->angle))
		*xo = -TILE_SIZE;
	else
		*xo = TILE_SIZE;
	*yo = get_rdy(TILE_SIZE, r->angle);
}

void	find_vertical_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		i;
	double	xo;
	double	yo;

	r = &mlx->ray;
	i = 0;
	first_vertical_side(mlx);
	if (is_wall2(r->vertical_x, r->vertical_y, r->angle))
		return ;
	vertical_offset(mlx, &xo, &yo);
	while (i++ < 20)
	{
		r->vertical_x += xo;
		r->vertical_y += yo;
		if (is_wall2(r->vertical_x, r->vertical_y, r->angle))
			break ;
		if (is_limit2(r->vertical_x, r->vertical_y))
			break ;
	}
}

void	first_horizontal_side(t_mlx *mlx)
{
	t_ray	*r;
	double	rdx;

	r = &mlx->ray;
	if (looking_up(r->angle))
		r->horizontal_y = backward_square(r->horizontal_y);
	else
		r->horizontal_y = foward_square(r->horizontal_y);
	rdx = get_rdx(positive(r->horizontal_y - mlx->player.y), r->angle);
	r->horizontal_x += rdx;
}

void	horizontal_offset(t_mlx *mlx, double *xo, double *yo)
{
	t_ray	*r;

	r = &mlx->ray;
	if (looking_up(r->angle))
		*yo = -TILE_SIZE;
	else
		*yo = TILE_SIZE;
	*xo = get_rdx(TILE_SIZE, r->angle);
}

void	find_horizontal_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		i;
	double	xo;
	double	yo;

	r = &mlx->ray;
	first_horizontal_side(mlx);
	if (is_wall2(r->horizontal_x, r->horizontal_y, r->angle))
		return ;
	horizontal_offset(mlx, &xo, &yo);
	i = 0;
	while (i++ < 20)
	{
		r->horizontal_x += xo;
		r->horizontal_y += yo;
		if (is_wall2(r->horizontal_x, r->horizontal_y, r->angle))
			break ;
		if (is_limit2(r->horizontal_x, r->horizontal_y))
			break ;
	}
}

void	choose_axis(t_mlx *mlx)
{
	t_ray	*r;
	double	h_dist;
	double	v_dist;

	r = &mlx->ray;
	h_dist = get_distance(mlx->player.x, mlx->player.y, r->horizontal_x, r->horizontal_y, mlx);
	v_dist = get_distance(mlx->player.x, mlx->player.y, r->vertical_x, r->vertical_y, mlx);
	if (h_dist < v_dist)
	{
		r->x = r->horizontal_x;
		r->y = r->horizontal_y;
		r->is_base_x = 0;
		r->is_vertical = 0;
	}
	else
	{
		r->x = r->vertical_x;
		r->y = r->vertical_y;
		r->is_base_x = 1;
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
