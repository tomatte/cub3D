/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_vertical_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:35:33 by suzy              #+#    #+#             */
/*   Updated: 2023/08/27 15:57:31 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	first_vertical_side(t_mlx *mlx)
{
	t_ray	*r;
	double	rdy;

	r = &mlx->ray;
	if (looking_left(r->angle))
		r->vertical_x = backward_square(r->vertical_x);
	else
		r->vertical_x = foward_square(r->vertical_x);
	rdy = get_rdy(positive(r->vertical_x - mlx->player.x), r->angle);
	r->vertical_y += rdy;
}

static void	vertical_offset(t_mlx *mlx, double *xo, double *yo)
{
	t_ray	*r;

	r = &mlx->ray;
	if (looking_left(r->angle))
		*xo = -TILE_SIZE;
	else
		*xo = TILE_SIZE;
	*yo = get_rdy(TILE_SIZE, r->angle);
}

void	find_vertical_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		i;
	double	xo;
	double	yo;

	r = &mlx->ray;
	i = 0;
	first_vertical_side(mlx);

	if (is_wall2(r->vertical_x, r->vertical_y, r->angle, &mlx->game_data))
		return ;
	vertical_offset(mlx, &xo, &yo);
	while (i++ < 50)
	{
		r->vertical_x += xo;
		r->vertical_y += yo;
		if (is_wall2(r->vertical_x, r->vertical_y, r->angle, &mlx->game_data))
			break ;
		if (is_limit2(r->vertical_x, r->vertical_y))
			break ;
	}
}
