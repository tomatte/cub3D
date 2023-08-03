/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:14:52 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/02 17:55:46 by suzy             ###   ########.fr       */
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

static unsigned int	get_texture_color(t_mlx *mlx, int *j, int i)
{
	double	w_mod;
	double	h_mod;
	int	color_index;
	int	column;
	int	line;
	int	h_index;
	int	w_index;

	w_mod = (double) mlx->texture_width / TILE_SIZE;
	h_mod = (double) mlx->texture_height / TILE_SIZE;
	
	h_index = i / h_mod;
	w_index = (*j) / w_mod;
	line = mlx->texture_width * h_index;
	column = w_index;
	//print line calculation
/* 	printf("hmod: %lf  |  width: %d  |  h_index: %d  |  i: %d  |  test: %d\n", h_mod, mlx->texture_width, h_index, i, 0/99);
	printf("column: %d  |  line: %d\n", column, line);
	if (*j) {exit(1);} */
	return (mlx->texture_addr[column + line]);
}

/*TODO: 
	colocar as cores da textura em um array de inteiros para mais fácil manipulação.
 */

void	draw_line_textured(t_mlx *mlx, t_line line, int size)
{
	static int		j = 0;
	unsigned int	color;
	int	i;

	//printf("texture_color: %u\n", get_texture_color(mlx, &j, 3)); exit(0);
	asign_values(&line);
	i = -1;
	while (++i <= line.longest)
	{
		color = get_texture_color(mlx, &j, i);
		//printf("texture_color: %u\n", color);
		set_color(color);
		my_mlx_pixel_put(mlx, line.x, line.y);
		line.proportion += line.shortest;
		walk_pixel(&line);
	}
	j++;
	if (j > mlx->texture_width - 1)
		j = 0;
}
