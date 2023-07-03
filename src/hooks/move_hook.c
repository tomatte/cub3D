/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:19:31 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 00:41:45 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	move(int key, t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	set_color(0x0);
	draw_player(mlx);
	set_color(DEFAULT_COLOR);
	if  (key == ARROW_UP)
	{
		p->x += p->delta_x;
		p->y += p->delta_y;
	}
	if  (key == ARROW_DOWN)
	{
		p->x -= p->delta_x;
		p->y -= p->delta_y;
	}
	if  (key == ARROW_RIGHT)
	{
		p->angle += 0.1;
		if (p->angle > 2 * PI)
			p->angle = 0;
		p->delta_x = cos(p->angle);
		p->delta_y = sin(p->angle);
	}
	if  (key == ARROW_LEFT)
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle = 2 * PI;
		p->delta_x = cos(p->angle);
		p->delta_y = sin(p->angle);
	}
	draw_player(mlx);
	put_image(mlx);
	return (1);
}

/* static int	stop_move(int key, t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if  (key == ARROW_UP)
		p->move_u = 0;
	if  (key == ARROW_DOWN)
		p->move_d = 0;
	if  (key == ARROW_RIGHT)
		p->move_r = 0;
	if  (key == ARROW_LEFT)
		p->move_l = 0;
	return (1);
}
 */
void	move_hook(t_mlx *mlx)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, move, mlx);
	//mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, stop_move, mlx);
}
