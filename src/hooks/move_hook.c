/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:19:31 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/02 23:51:55 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	move(int key, t_mlx *mlx)
{
	//static int	test = 0;

	if  (key == ARROW_UP)
		mlx->player.move_u = -0.2;
	if  (key == ARROW_DOWN)
		mlx->player.move_d = 0.2;
	if  (key == ARROW_RIGHT)
		mlx->player.move_r = 0.2;
	if  (key == ARROW_LEFT)
		mlx->player.move_l = -0.2;
	return (1);
}

static int	stop_move(int key, t_mlx *mlx)
{
	//static int	test = 0;

	if  (key == ARROW_UP)
		mlx->player.move_u = 0;
	if  (key == ARROW_DOWN)
		mlx->player.move_d = 0;
	if  (key == ARROW_RIGHT)
		mlx->player.move_r = 0;
	if  (key == ARROW_LEFT)
		mlx->player.move_l = 0;
	return (1);
}

void	move_hook(t_mlx *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, move, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, stop_move, mlx);
}
