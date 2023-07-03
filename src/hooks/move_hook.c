/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:19:31 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 12:24:30 by dbrandao         ###   ########.fr       */
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
		p->mv_angle_r = 0.01;
	if (key == ARROW_LEFT)
		p->mv_angle_l = -0.01;
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

void	move_hook(t_mlx *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, move, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, stop_move, mlx);
}
