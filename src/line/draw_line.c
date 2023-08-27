/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:14:52 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/23 09:43:49 by suzy             ###   ########.fr       */
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

static void	pick_color(t_mlx *mlx)
{
	t_ray			*r;
	t_texture		*texture;
	unsigned int	c;
	double			tile_img_proportion;
	int				x;
	int				y;

	texture = &mlx->texture;
	r = &mlx->ray;
	tile_img_proportion = texture->width / TILE_SIZE;
	x  = (int)  round(texture->tile_map_x * tile_img_proportion);
	y = (int)  round(texture->tile_map_y);
	if (x >= texture->width)
		x %= texture->width;
	if (y >= texture->height)
		y %= texture->height;
	else if (y < 0)
		y += texture->height;
	//printf("y: %d  |  x: %d  |  height: %d  |  width: %d\n", x, y, mlx->textures[mlx->texture_selected].height, mlx->textures[mlx->texture_selected].width);
	//printf("texture -> height: %d  |  width: %d\n", texture->height, texture->width);
	c = *(texture->colors[y][x]);
	set_color(c);
}

void	draw_line_textured(t_mlx *mlx, t_line line)
{
	t_ray		*r;
	t_texture	*texture;
	int			i;

	r = &mlx->ray;
	texture = &mlx->texture;
	texture->tile_map_y = texture->height - 1;
	asign_values(&line);
	i = -1;
	while (++i <= line.longest)
	{
		pick_color(mlx);
		my_mlx_pixel_put(mlx, line.x, line.y);
		line.proportion += line.shortest;
		walk_pixel(&line);
		texture->tile_map_y -= texture->vertical_proportion;
	}
}
