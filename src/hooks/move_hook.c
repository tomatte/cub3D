/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:19:31 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/09 18:59:56 by suzy             ###   ########.fr       */
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
		p->mv_angle_r = 0.02;
	if (key == ARROW_LEFT)
		p->mv_angle_l = -0.02;
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
		mlx_destroy_window(mlx->mlx, mlx->win);
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
