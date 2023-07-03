/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:19:31 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/02 23:09:00 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	move(int key, t_mlx *mlx)
{
	//static int	test = 0;

	if  (key == ARROW_UP)
		mlx->player.move_y = -1;
	if  (key == ARROW_DOWN)
		mlx->player.move_y = 1;
	if  (key == ARROW_RIGHT)
		mlx->player.move_x = 1;
	if  (key == ARROW_LEFT)
		mlx->player.move_x = -1;
	return (1);
}

static int	stop_move(int key, t_mlx *mlx)
{
	//static int	test = 0;

	if  (key == ARROW_UP)
		mlx->player.move_y = 0;
	if  (key == ARROW_DOWN)
		mlx->player.move_y = 0;
	if  (key == ARROW_RIGHT)
		mlx->player.move_x = 0;
	if  (key == ARROW_LEFT)
		mlx->player.move_x = 0;
	return (1);
}

void	move_hook(t_mlx *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, move, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, stop_move, mlx);
}
