/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/29 17:17:12 by dbrandao         ###   ########.fr       */
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

void	dda_ray(t_mlx *mlx)
{
	t_ray		*r;
	t_player	*p;

	r = &mlx->ray;
	p = &mlx->player;
	printf("x: %lf |  backward: %lf  |  forward: %lf \n", p->x, backward_square(p->x), foward_square(p->x));
	printf("y: %lf |  backward: %lf  |  forward: %lf \n", p->y, backward_square(p->y), foward_square(p->y));
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
	//dda_ray(mlx);
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	eraser(mlx);
	update_player_position(mlx);
	draw_2d_blocks(mlx, TILE_SIZE);
	draw_player(mlx);
	set_color(RED);
	dda_ray(mlx);
	set_color(DEFAULT_COLOR);
	put_image(mlx);
	return (1);
}
