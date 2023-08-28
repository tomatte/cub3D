/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:43:34 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 22:20:03 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	positive(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

double	negative(double num)
{
	if (num > 0)
		return (num * -1);
	return (num);
}

int	looking_up(double angle)
{
	if (angle > PI)
		return (1);
	return (0);
}

int	looking_left(double angle)
{
	if (angle > PI / 2 && angle < PI + PI / 2)
		return (1);
	return (0);
}

t_vector	new_vec(double x, double y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}
