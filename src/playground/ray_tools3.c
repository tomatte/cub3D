/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:15:36 by suzy              #+#    #+#             */
/*   Updated: 2023/08/27 17:49:23 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
}

double	round_base(double num, int base)
{
	double	result;

	result = round(num / (double) base) * base;
	return (result);
}

void	pick_color(t_mlx *mlx)
{
	t_texture		*texture;
	unsigned int	c;
	double			tile_img_proportion;
	int				x;
	int				y;

	texture = &mlx->texture;
	tile_img_proportion = texture->width / TILE_SIZE;
	x = (int) round(texture->tile_map_x * tile_img_proportion);
	y = (int) round(texture->tile_map_y);
	if (x >= texture->width)
		x %= texture->width;
	if (y >= texture->height)
		y %= texture->height;
	else if (y < 0)
		y += texture->height;
	c = *(texture->colors[y][x]);
	set_color(c);
}

int	is_wall2(double rx, double ry, double angle, t_game_data *game)
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
	if (x < 0 || x >= game->line_length || y < 0 || y >= game->map_lines)
		return (-1);
	return (ft_strchr("0N", game->map_data[y][x]) == NULL);
}
