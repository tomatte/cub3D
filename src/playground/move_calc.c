/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:24:11 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/26 23:31:52 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	set_player_direction(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	p->angle += p->mv_angle_r / 2;
	if (p->angle > 2 * PI)
		p->angle = 0;
	p->angle += p->mv_angle_l / 2;
	if (p->angle < 0)
		p->angle = 2 * PI;
	p->delta_x = cos(p->angle);
	p->delta_y = sin(p->angle);
}

static void	move_player(t_mlx *mlx)
{
	const double	slow = 0.2;
	t_player		*p;

	p = &mlx->player;
	if (p->mv_up)
	{
		p->x += p->delta_x / slow;
		p->y += p->delta_y / slow;
	}
	if (p->mv_down)
	{
		p->x -= p->delta_x / slow;
		p->y -= p->delta_y / slow;
	}
	if (p->mv_left)
	{
		p->x -= cos(p->angle + PI / 2) / slow;
		p->y -= sin(p->angle + PI / 2) / slow;
	}
	if (p->mv_right)
	{
		p->x += cos(p->angle + PI / 2) / slow;
		p->y += sin(p->angle + PI / 2) / slow;
	}
}

static void	move_limit(t_mlx *mlx)
{
	if (mlx->player.x < 0)
		mlx->player.x = 0;
	if (mlx->player.y < 0)
		mlx->player.y = 0;
/* 	if (mlx->player.y + P_SIZE > SCREEN_HEIGHT)
		mlx->player.y = SCREEN_HEIGHT - P_SIZE;
	if (mlx->player.x + P_SIZE > SCREEN_WIDTH)
		mlx->player.x = SCREEN_WIDTH - P_SIZE; */
}

void	update_player_position(t_mlx *mlx)
{
	set_player_direction(mlx);
	move_player(mlx);
	move_limit(mlx);
}
