/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:19:31 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 22:17:10 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	move(int key, t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (key == ARROW_UP || key == 'w')
		p->mv_up = 1;
	if (key == ARROW_DOWN || key == 's')
		p->mv_down = 1;
	if (key == 'a')
		p->mv_left = 1;
	if (key == 'd')
		p->mv_right = 1;
	if (key == ARROW_RIGHT)
		p->mv_angle_r = 0.05;
	if (key == ARROW_LEFT)
		p->mv_angle_l = -0.05;
	return (1);
}

static int	stop_move(int key, t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (key == ARROW_UP || key == 'w')
		p->mv_up = 0;
	if (key == ARROW_DOWN || key == 's')
		p->mv_down = 0;
	if (key == 'a')
		p->mv_left = 0;
	if (key == 'd')
		p->mv_right = 0;
	if (key == ARROW_RIGHT)
		p->mv_angle_r = 0;
	if (key == ARROW_LEFT)
		p->mv_angle_l = 0;
	return (1);
}

static int	esc_close_window(int key, t_mlx *mlx)
{
	if (key == ESC_KEY)
	{
		destroy_mlx(mlx);
		exit(0);
	}
	return (0);
}

static int	key_press_handler(int key, t_mlx *mlx)
{
	move(key, mlx);
	esc_close_window(key, mlx);
	return (0);
}

void	move_hook(t_mlx *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_press_handler, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, stop_move, mlx);
}
