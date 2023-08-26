/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:10:11 by suzy              #+#    #+#             */
/*   Updated: 2023/08/26 14:54:21 by suzy             ###   ########.fr       */
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
