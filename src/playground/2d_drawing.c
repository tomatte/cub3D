/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:20:06 by suzy              #+#    #+#             */
/*   Updated: 2023/08/02 14:50:25 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	draw_direction_line(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	draw_line(
		mlx,
		points(
			round(p->x + P_SIZE / 2),
			round(p->y + P_SIZE / 2),
			round(p->x + (P_SIZE / 2) + (p->delta_x * 20)),
			round(p->y + (P_SIZE / 2) + (p->delta_y * 20))
			)
		);
}

void	draw_player(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	square2(mlx, (int) round(p->x), (int) round(p->y), P_SIZE);
	draw_direction_line(mlx);
}
