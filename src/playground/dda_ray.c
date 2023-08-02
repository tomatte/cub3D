/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:14:08 by suzy              #+#    #+#             */
/*   Updated: 2023/08/02 14:16:18 by suzy             ###   ########.fr       */
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

	r = &mlx->ray;
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
}

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
	t_ray	*r;
	int		i = 0;

	r = &mlx->ray;
	r->x = mlx->player.x + P_SIZE / 2;
	r->y = mlx->player.y + P_SIZE / 2;
	r->map_x = (int) (r->x / TILE_SIZE);
	r->map_y = (int) (r->y / TILE_SIZE);
	while (i++ < 16)
	{
		calc_next_column_values(mlx);
		calc_next_row_values(mlx);
		jump_to_next_square(mlx);
		if (is_wall(mlx))
			break ;
		if (r->map_x < 0 || r->map_x > 14 || r->map_y < 0 || r->map_y > 10)
			break ;
	}
}