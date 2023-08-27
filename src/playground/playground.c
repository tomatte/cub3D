/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/27 18:42:26 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_background(t_mlx *mlx)
{
	t_vector	vector;

	set_color(mlx->game_data.parameters.top_color);
	vector.x = 0;
	vector.y = 0;
	rectangle(mlx, vector, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	set_color(mlx->game_data.parameters.bottom_color);
	vector.x = 0;
	vector.y = SCREEN_HEIGHT / 2;
	rectangle(mlx, vector, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
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
