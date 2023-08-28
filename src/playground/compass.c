/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:10:11 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 22:18:29 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_east(double angle, int is_vertical)
{
	if (!is_vertical)
		return (0);
	return (!looking_left(angle));
}

int	is_west(double angle, int is_vertical)
{
	if (!is_vertical)
		return (0);
	return (looking_left(angle));
}

int	is_north(double angle, int is_vertical)
{
	if (is_vertical)
		return (0);
	return (looking_up(angle));
}

int	is_south(double angle, int is_vertical)
{
	if (is_vertical)
		return (0);
	return (!looking_up(angle));
}
