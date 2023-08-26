/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/25 23:55:56 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_background(t_mlx *mlx)
{
	set_color(OCEAN);
	rectangle(mlx, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	set_color(LIME);
	rectangle(mlx, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	set_color(DEFAULT_COLOR);
}

static void	eraser(t_mlx *mlx)
{
	set_color(0x0);
	multiple_rays(mlx);
	// draw_2d_blocks(mlx, TILE_SIZE);
	// dda_ray(mlx);
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	eraser(mlx);
	update_player_position(mlx);
	draw_background(mlx);
	set_color(RED);
	// dda_ray(mlx);
	multiple_rays(mlx);
	set_color(DEFAULT_COLOR);
	// draw_2d_blocks(mlx, TILE_SIZE);
	put_image(mlx);
	return (1);
}
