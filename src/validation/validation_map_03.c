/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:25:01 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/18 23:11:40 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_tf	geom_crawl(char **map_array, int x_cor, int y_cor, char cha_put)
{
	while (1)
	{
		if (map_array[x_cor + 1] && map_array[x_cor + 1][y_cor] == OUTLINE)
			map_array[x_cor++][y_cor] = cha_put;
		else if (y_cor > 0 && map_array[x_cor][y_cor - 1] == OUTLINE)
			map_array[x_cor][y_cor--] = cha_put;
		else if (x_cor > 0 && map_array[x_cor - 1][y_cor] == OUTLINE)
			map_array[x_cor--][y_cor] = cha_put;
		else if (map_array[x_cor][y_cor + 1] == OUTLINE)
			map_array[x_cor][y_cor++] = cha_put;
		else if (break_check(map_array, x_cor, y_cor, cha_put))
		{
			map_array[x_cor][y_cor] = cha_put;
			return (TRUE);
		}
		else
			return (FALSE);
		if (geom_fork(map_array, x_cor, y_cor))
		{
			if (geom_recur(map_array, x_cor, y_cor))
			{
				return (TRUE);
			}
		}
	}
}

int	break_check(char **map_array, int x_cord, int y_cord, char cha)
{
	return ((y_cord > 0 && map_array[x_cord][y_cord + 1] == cha && \
				map_array[x_cord][y_cord - 1] == cha) \
		|| (x_cord > 0 && map_array[x_cord + 1] && \
				map_array[x_cord + 1][y_cord] == cha && \
				map_array[x_cord - 1][y_cord] == cha) \
		|| (x_cord > 0 && map_array[x_cord - 1][y_cord] == cha && \
				map_array[x_cord][y_cord + 1] == cha) \
		|| (x_cord > 0 && y_cord > 0 && \
				map_array[x_cord][y_cord - 1] == cha && \
				map_array[x_cord - 1][y_cord] == cha) \
		|| (y_cord > 0 && map_array[x_cord + 1] && \
				map_array[x_cord + 1][y_cord] == cha && \
				map_array[x_cord][y_cord - 1] == cha) \
		|| (map_array[x_cord + 1] && \
				map_array[x_cord + 1][y_cord] == cha && \
				map_array[x_cord][y_cord + 1] == cha));
}

t_tf	geom_fork(char **map_array, int x_cord, int y_cord)
{
	int	counter;

	counter = 0;
	if (map_array[x_cord][y_cord + 1] == OUTLINE)
	{
		counter++;
	}
	if (y_cord > 0 && map_array[x_cord][y_cord - 1] == OUTLINE)
	{
		counter++;
	}
	if (map_array[x_cord + 1] && map_array[x_cord + 1][y_cord] == OUTLINE)
	{
		counter++;
	}
	if (x_cord > 0 && map_array[x_cord - 1][y_cord] == OUTLINE)
	{
		counter++;
	}
	if (counter < 2)
	{
		return (FALSE);
	}
	return (TRUE);
}

t_tf	geom_recur(char **map_array, int x_cord, int y_cord)
{
	if (map_array[x_cord + 1] && map_array[x_cord + 1][y_cord] == OUTLINE)
	{
		return (geom_crawl(map_array, x_cord + 1, y_cord, OUTER_EDGE));
	}
	if (y_cord > 0 && map_array[x_cord][y_cord - 1] == OUTLINE)
	{
		return (geom_crawl(map_array, x_cord, y_cord - 1, OUTER_EDGE));
	}
	if (x_cord > 0 && map_array[x_cord - 1][y_cord] == OUTLINE)
	{
		return (geom_crawl(map_array, x_cord - 1, y_cord, OUTER_EDGE));
	}
	if (map_array[x_cord][y_cord + 1] == OUTLINE)
	{
		return (geom_crawl(map_array, x_cord, y_cord + 1, OUTER_EDGE));
	}
	return (FALSE);
}

t_tf	player_in(char **map_ar, int line, int collum)
{
	while (map_ar[++line])
	{
		while (map_ar[line][++collum])
		{
			if (map_ar[line][collum] == OUTER_EDGE)
			{
				while (map_ar[line][collum] && \
						map_ar[line][++collum] == OUTER_EDGE)
					continue ;
				if (ft_strchr(&map_ar[line][collum], OUTER_EDGE))
				{
					while (map_ar[line][collum] != OUTER_EDGE)
					{
						if (in_group(map_ar[line][collum], PLAYER_VALID))
							return (TRUE);
						collum++;
					}
				}
			}
			if (!map_ar[line][collum])
				collum--;
		}
		collum = -1;
	}
	return (FALSE);
}
