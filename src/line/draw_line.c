/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:14:52 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/09 18:48:40 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	walk_longest(t_line *line)
{
	line->proportion -= line->longest;
	line->x += line->dx1;
	line->y += line->dy1;
}

static void	walk_both(t_line *line)
{
	line->x += line->dx2;
	line->y += line->dy2;
}

static void	walk_pixel(t_line *line)
{
	if (line->proportion >= line->longest)
		walk_longest(line);
	else
		walk_both(line);
}

void	draw_line(t_mlx *mlx, t_line line)
{
	int	i;

	asign_values(&line);
	i = 0;
	while (i++ <= line.longest)
	{
		my_mlx_pixel_put(mlx, line.x, line.y);
		line.proportion += line.shortest;
		walk_pixel(&line);
	}
}

static int	color_line(t_mlx *mlx, int line_index)
{
	int	color_line;

	color_line = mlx->texture_width * line_index;
	return (color_line);
}

static void	pick_color(t_mlx *mlx)
{
	t_ray			*r;
	unsigned int	c;
	double			tile_img_proportion;
	int				x;
	int				y;

	tile_img_proportion = mlx->texture_width / TILE_SIZE;
	r = &mlx->ray;
	x  = (int)  round(r->tile_map_x * tile_img_proportion);
	y = (int)  round(r->tile_map_y);
	if (x > mlx->texture_width - 1)
		x = mlx->texture_width - 1;
	if (y > mlx->texture_height - 1)
		y = mlx->texture_height - 1;
	//printf("x: %d  |  y: %d\n", x, y);
	c = *(mlx->texture_colors[y][x]);
	set_color(c);
}

void	draw_line_textured(t_mlx *mlx, t_line line, int size)
{
	t_ray	*r;
	int	i;

	r = &mlx->ray;
	r->tile_map_y = 0;
	asign_values(&line);
	i = -1;
	while (++i <= line.longest)
	{
		pick_color(mlx);
		my_mlx_pixel_put(mlx, line.x, line.y);
		line.proportion += line.shortest;
		walk_pixel(&line);
		r->tile_map_y += mlx->ray.vertial_proportion;
		//printf("img_y: %lf\n", img_y);
	}
	//exit(0);
}
