/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:14:08 by suzy              #+#    #+#             */
/*   Updated: 2023/08/16 09:45:43 by suzy             ###   ########.fr       */
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

double	get_distance(double old_x, double old_y, double x, double y)
{
	double	h;

	h = sqrt(pow(positive(x - old_x), 2) + pow(positive(y - old_y), 2));
	return (h);
}

int	is_border_north(t_mlx *mlx)
{
	
}

static double	fix_base_y_border(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	double	diff_y;

	diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	if (is_wall(mlx) && diff_y < 1)
	{
		r->x = r->row_x;
		r->y = r->row_y;
		r->is_base_x = 0;
	}
}

static double	fix_base_x_border(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	double	diff_x;

	diff_x = positive(positive(r->rdx_col) - positive(r->rdx_row));
	if (is_wall(mlx) && diff_x < 1 && r->is_base_x)
	{
		r->x = r->column_x;
		r->y = r->column_y;
		r->is_base_x = 1;
	}
}

void	jump_to_next_square(t_mlx *mlx)
{
	t_ray	*r;
	double	col_pixels;
	double	row_pixels;
	double	col_distance;
	double	row_distance;

	r = &mlx->ray;
	col_pixels = positive(r->rdx_col) + positive(r->rdy_col);
	row_pixels = positive(r->rdx_row) + positive(r->rdy_row);
	col_distance = get_distance(r->x, r->y, r->column_x, r->column_y);
	row_distance = get_distance(r->x, r->y, r->row_x, r->row_y);
 	if (col_distance < row_distance || r->rdy_col == 0)
	{
		r->x = r->column_x;
		r->y = r->column_y;
		r->is_base_x = 1;
	}
	else
	{
		r->x = r->row_x;
		r->y = r->row_y;
		r->is_base_x = 0;
	}
	//fix_base_x_border(mlx);
	static double max_dist = 0;
	static double max_diff_y = 0;
	static double max_diff_x = 0;
	double distance_diff = positive(col_distance - row_distance);
	double diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	double diff_x = positive(positive(r->rdx_col) - positive(r->rdx_row));
	if (is_wall(mlx) && diff_y < 1)
	{
		if (distance_diff > max_dist)
			max_dist = distance_diff;
		if (diff_y > max_diff_y)
			max_diff_y = diff_y;
		if (diff_x > max_diff_x)
			max_diff_x = diff_x;
		printf("column_x: %lf  |  column_y: %lf  |  row_x: %lf  |  row_y: %lf\n", r->column_x, r->column_y, r->row_x, r->row_y);
		printf("col_distance: %lf  |  row_distance: %lf  |  is_base_x: %lf\n", col_distance, row_distance, r->is_base_x);
		printf("distance diff: %lf  |  max_dist: %lf  |  max_diff_y: %lf  |  max_diff_x: %lf\n", distance_diff, max_dist, max_diff_y, max_diff_x);
		//printf("----------------------------------------------------\n");
	}
	fix_base_y_border(mlx);
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
	return (map[y][x]);
}

int	is_old_wall(double angle, double old_x, double old_y)
{
	int		x;
	int		y;

	if (looking_left(angle))
		x = (int)(old_x / TILE_SIZE);
	else
		x = (int)(ceil(old_x) / TILE_SIZE);
	if (looking_up(angle))
		y = (int)(old_y / TILE_SIZE);
	else
		y = (int)(ceil(old_y) / TILE_SIZE);
	return (map[y][x]);
}

void debug1(t_mlx *mlx, int show, int index)
{
	t_ray	*r;
	static double	old_x;
	static double	old_y;
	static int		old_index;

	r = &mlx->ray;
	if (show && ((int)r->x == 192 || (int)r->x == 256 || (int)r->x == 320))
	{
		printf("before_x: %lf  |  before_y: %lf  |  is_old_wall: %d  |  is_wall: %d  |  old_index: %d  |  index: %d\n", old_x, old_y, is_old_wall(r->angle, old_x, old_y), is_wall(mlx), old_index, index);
		return ;
	}
	old_x = r->x;
	old_y = r->y;
	old_index = index;
}

void	dda_ray(t_mlx *mlx)
{
	t_ray	*r;
	int		i;
	double test_col;
	double test_row;

	r = &mlx->ray;
	r->x = mlx->player.x;
	r->y = mlx->player.y;
	r->map_x = (int)(r->x / TILE_SIZE);
	r->map_y = (int)(r->y / TILE_SIZE);
	i = 0;
	while (i++ < 100)
	{
		calc_next_column_values(mlx);
		calc_next_row_values(mlx);
		jump_to_next_square(mlx);
		if (is_wall(mlx))
		{
			//debug1(mlx, 1, i);
			break ;
		}
		else
		{
			debug1(mlx, 0, i);
		}
	}
}
