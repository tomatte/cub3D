/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:14:52 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/31 23:55:27 by dbrandao         ###   ########.fr       */
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

void	draw_line2(t_mlx *mlx, t_line line, int index)
{
	int	i;
	int	mod;

	asign_values(&line);
	mod = line.longest / 64;
	if (mod <= 0)
		mod = 1;
	i = -1;
	while (++i <= line.longest)
	{
		if (i % mod == 0)
			set_color(mlx->texture_addr[i / mod + (64 * index)]);
		my_mlx_pixel_put(mlx, line.x, line.y);
		line.proportion += line.shortest;
		walk_pixel(&line);
	}
}
