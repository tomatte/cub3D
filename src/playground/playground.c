/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/02 18:39:09 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


static void	draw_2_lines(t_mlx *mlx)
{
	draw_line2(mlx, points(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2), RED);
	draw_line2(mlx, points(0, SCREEN_HEIGHT / 2 + 20, SCREEN_WIDTH, SCREEN_HEIGHT / 2 + 20), DEFAULT_COLOR);
}

void	playground(t_mlx *mlx)
{
	draw_2_lines(mlx);
	put_image(mlx);
}
