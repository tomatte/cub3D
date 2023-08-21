/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/20 23:34:03 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_texture	select_texture(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (r->x > r->old_x)
		mlx->texture_selected = NORTH;
	else if (r->y > r->old_y)
		mlx->texture_selected = EAST;
	else if (r->x < r->old_x)
		mlx->texture_selected = SOUTH;
	else
		mlx->texture_selected = WEST;
	return (mlx->textures[mlx->texture_selected]);
}

static void	first_texture_calculation(t_mlx *mlx)
{
	t_texture	*texture;
	t_ray		*r;

	texture = &mlx->texture;
	r = &mlx->ray;
	//printf("rx: %lf  | ry: %lf\n", r->x, r->y);
	if (r->is_base_x)
		texture->tile_map_x = (int) round(r->y) % TILE_SIZE;
	else
		texture->tile_map_x = (int) round(r->x) % (TILE_SIZE - 1);
	//printf("map_x: %lf  |  map_y: %lf\n", texture->tile_map_x, texture->tile_map_y);
	texture->vertical_proportion = texture->height / r->line_length;
}

/* TO-DO
	change the select texture function to not use old_x and old_y
 */

static void	debugg(t_mlx *mlx)
{
	t_ray	*r;
	double test_col;
	double test_row;
	double	diff;
	double	diff_y;
	double	diff_x;

	r = &mlx->ray;
	test_col = positive(r->rdx_col) + positive(r->rdy_col);
	test_row = positive(r->rdx_row) + positive(r->rdy_row);
	diff = positive(test_col - test_row);
	diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	diff_x = positive(positive(r->rdx_col) - positive(r->rdx_row));
	if (is_wall(mlx) && ((r->y >= 127 && r->y < 128.5) || (r->y >= 191 && r->y < 192.5)))
	{
		printf("rdy_row: %lf  |  rdx_row: %lf\n", r->rdy_row, r->rdx_row);
		printf("rdy_col: %lf  |  rdx_col: %lf\n", r->rdy_col, r->rdx_col);
		printf("column_x: %lf  |  column_y: %lf\n", r->column_x, r->column_y);
		printf("row_x: %lf  |  row_y: %lf\n", r->row_x, r->row_y);
		printf("test_col: %lf  |  test_row: %lf\n", test_col, test_row);
		printf("diff: %lf  |  diff_y: %lf  |  diff_x: %lf\n", diff, diff_y, diff_x);
		printf("angle: %lf\n", r->angle);
		int txtr = mlx->texture_selected;
		printf("Texture selected: %s\n", txtr == NORTH ? "North" : txtr == SOUTH ? "South" : txtr == WEST ? "West" : "East");
		printf("--------------------------------------------------------\n");
	}
}

static void	transform_to_3d(t_mlx *mlx, int i)
{
	t_ray		*r;
	t_texture	*texture;
	double		nx;
	double		ny;

	r = &mlx->ray;
	mlx->texture = select_texture(mlx);
	debugg(mlx);
	texture = &mlx->texture;
	r->line_length = (SCREEN_HEIGHT * TILE_SIZE) / get_ray_distance(mlx);
	first_texture_calculation(mlx);
	ny = SCREEN_HEIGHT / 2;
	r->line_begin = ny + (r->line_length / 2);
	r->line_end = ny - (r->line_length / 2);
	draw_line_textured(mlx, points(i, r->line_begin, i, r->line_end), -9999999);
}

void	multiple_rays(t_mlx *mlx)
{
	double		ray_mod;
	double		sum;
	double		vision_angle;
	double		limit_angle;
	t_player	*p;
	t_ray		*r;
	int			i;

	i = -1;
	p = &mlx->player;
	r = &mlx->ray;
	vision_angle = degrees_to_radians(VISION_ANGLE);
	ray_mod = vision_angle / TOTAL_RAYS;
	limit_angle = vision_angle / 2;
	sum = limit_angle * -1;

	r->angle = normalize_angle(p->angle + sum);
	dda_ray(mlx);
	r->old_x = r->x;
	r->old_y = r->y;
	while (sum < limit_angle)
	{
		r->angle = normalize_angle(p->angle + sum);
		dda_ray(mlx);
		transform_to_3d(mlx, ++i);
		sum += ray_mod;
		r->old_x = r->x;
		r->old_y = r->y;
	}
}
