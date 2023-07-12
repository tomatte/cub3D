/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:43:34 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/12 00:51:47 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	dmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	positive(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	looking_up(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (p->angle > PI)
	{
		return (1);
	}
	return (0);
}

int	looking_left(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (p->angle > PI / 2 && p->angle < PI + PI / 2)
	{
		return (1);
	}
	return (0);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}
