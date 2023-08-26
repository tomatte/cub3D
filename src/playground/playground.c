/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/26 14:18:12 by suzy             ###   ########.fr       */
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
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	eraser(mlx);
	update_player_position(mlx);
	draw_background(mlx);
	multiple_rays(mlx);
	put_image(mlx);
	return (1);
}
