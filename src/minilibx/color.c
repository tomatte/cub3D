/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:07:33 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/02 19:18:46 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	**color_singleton(void)
{
	static int	*color_s = NULL;

	return (&color_s);
}

void	init__color(int *color)
{
	int	**color_s;

	color_s = color_singleton();
	*color_s = color;
}

void	set_color(int color)
{
	int	**color_s;

	color_s = color_singleton();
	**color_s = color;
}
