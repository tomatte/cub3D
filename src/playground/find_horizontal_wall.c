/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_horizontal_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:35:00 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 22:19:08 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	first_horizontal_side(t_mlx *mlx)
{
	t_ray	*r;
	double	rdx;

	r = &mlx->ray;
	if (looking_up(r->angle))
		r->horizontal_y = backward_square(r->horizontal_y);
	else
		r->horizontal_y = foward_square(r->horizontal_y);
	rdx = get_rdx(positive(r->horizontal_y - mlx->player.y), r->angle);
	r->horizontal_x += rdx;
}

static void	horizontal_offset(t_mlx *mlx, double *xo, double *yo)
{
	t_ray	*r;

	r = &mlx->ray;
	if (looking_up(r->angle))
		*yo = -TILE_SIZE;
	else
		*yo = TILE_SIZE;
	*xo = get_rdx(TILE_SIZE, r->angle);
}

void	find_horizontal_wall(t_mlx *mlx)
{
	t_ray		*r;
	int			i;
	double		xo;
	double		yo;
	t_game_data	*game;

	game = &mlx->game_data;
	r = &mlx->ray;
	first_horizontal_side(mlx);
	if (is_wall2(r->horizontal_x, r->horizontal_y, r->angle, &mlx->game_data))
		return ;
	horizontal_offset(mlx, &xo, &yo);
	i = 0;
	while (i++ < 50)
	{
		r->horizontal_x += xo;
		r->horizontal_y += yo;
		if (is_wall2(r->horizontal_x, r->horizontal_y, r->angle, game))
			break ;
		if (is_limit2(r->horizontal_x, r->horizontal_y))
			break ;
	}
}
