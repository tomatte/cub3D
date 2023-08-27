/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:15:36 by suzy              #+#    #+#             */
/*   Updated: 2023/08/26 15:15:46 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
}

double	round_base(double num, int base)
{
	double	result;

	result = round(num / (double) base) * base;
	return (result);
}
