/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:41:15 by dbrandao          #+#    #+#             */
/*   Updated: 2023/06/28 15:42:34 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_line	points(int x, int y, int x2, int y2)
{
	t_line	line;

	ft_bzero(&line, sizeof(line));
	line.color = DEFAULT_COLOR;
	line.x = x;
	line.y = y;
	line.x2 = x2;
	line.y2 = y2;
	return (line);
}
