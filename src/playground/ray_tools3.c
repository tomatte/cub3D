/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:15:36 by suzy              #+#    #+#             */
/*   Updated: 2023/08/26 17:04:53 by suzy             ###   ########.fr       */
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
