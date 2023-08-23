/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:10:11 by suzy              #+#    #+#             */
/*   Updated: 2023/08/21 15:34:16 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_east(double x, double y)
{
	if (has_floats(x))
		return (0);
	if ((int) x % TILE_SIZE != 0)
		return (0);
	return (1);
}

int	is_west(double x, double y)
{
	if (has_floats(x))
		return (0);
	if ((int) (x + 1) % TILE_SIZE != 0)
		return (0);
	return (1);
}

int is_north(double x, double y)
{
	if (has_floats(y))
		return (0);
	if ((int) (y + 1) % TILE_SIZE != 0)
		return (0);
	return (1);
}

int is_south(double x, double y)
{
	if (has_floats(y))
		return (0);
	if ((int) y % TILE_SIZE != 0)
		return (0);
	return (1);
}
