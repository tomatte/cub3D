/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:10:11 by suzy              #+#    #+#             */
/*   Updated: 2023/08/21 10:14:34 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_east(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (has_floats(r->x))
		return (0);
	if ((int) r->x % TILE_SIZE != 0)
		return (0);
	return (1);
}

int	is_west(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (has_floats(r->x))
		return (0);
	if ((int) (r->x + 1) % TILE_SIZE != 0)
		return (0);
	return (1);
}

int is_north(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (has_floats(r->y))
		return (0);
	if ((int) (r->y + 1) % TILE_SIZE != 0)
		return (0);
	return (1);
}

int is_south(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (has_floats(r->y))
		return (0);
	if ((int) r->y % TILE_SIZE != 0)
		return (0);
	return (1);
}
