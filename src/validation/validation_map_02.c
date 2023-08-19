/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:21:34 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/19 01:26:57 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	map_outline(char **map_array)
{
	int	line;
	int	collum;

	line = -1;
	collum = -1;
	while (map_array[++line])
	{
		while (map_array[line][++collum])
		{
			if (map_array[line][collum] == '1')
			{
				if (cha_border(map_array, line, collum, ' ') == TRUE)
				{
					map_array[line][collum] = OUTLINE;
				}
			}
		}
		collum = -1;
	}
}

t_tf	cha_border(char **map_array, int xcord, int ycord, char cha)
{
	if (xcord == 0 || ycord == 0 || map_array[xcord][ycord + 1] \
			== '\0' || map_array[xcord + 1] == NULL)
	{
		return (TRUE);
	}
	if (map_array[xcord - 1][ycord - 1] == cha
			|| map_array[xcord][ycord - 1] == cha
			|| map_array[xcord + 1][ycord - 1] == cha
			|| map_array[xcord - 1][ycord] == cha
			|| map_array[xcord + 1][ycord] == cha
			|| map_array[xcord - 1][ycord + 1] == cha
			|| map_array[xcord][ycord + 1] == cha
			|| map_array[xcord + 1][ycord + 1] == cha)
	{
		return (TRUE);
	}
	return (FALSE);
}

void	map_nu_walls(char **map_array)
{
	int	line;
	int	collum;

	line = -1;
	collum = -1;
	while (map_array[++line])
	{
		while (map_array[line][++collum])
		{
			if (map_array[line][collum] == OUTLINE)
			{
				if (cha_border(map_array, line, collum, '0') == FALSE
					&& cha_border(map_array, line, collum, '1') == FALSE)
				{
					map_array[line][collum] = SPACE_FILLER;
				}
			}
		}
		collum = -1;
	}
}

t_tf	stuck_player(char **map_ar)
{
	t_cords	cor;
	t_tf	bool;

	cor = cordinates_obtain(map_ar, 0, 0);
	bool = TRUE;
	if (cor.x == 0 || map_ar[cor.x][cor.y + 1] == '\0')
		return (FALSE);
	while (map_ar[cor.x][cor.y] && map_ar[cor.x][cor.y] != OUTLINE)
		cor.y++;
	while (bool)
	{
		bool = geom_crawl(map_ar, cor.x, cor.y, OUTER_EDGE);
		while (!player_in(map_ar, -1, -1))
		{
			change_cha_array(map_ar, "!", "@");
			cor = cordinates_obtain(map_ar, 0, 0);
			if (cor.x == 0 || !ft_strchr(&map_ar[cor.x][cor.y], OUTLINE))
				return (FALSE);
			while (map_ar[cor.x][cor.y] && map_ar[cor.x][cor.y] != OUTLINE)
				cor.y++;
			bool = geom_crawl(map_ar, cor.x, cor.y, OUTER_EDGE);
		}
		return (bool);
	}
	return (FALSE);
}

t_cords	cordinates_obtain(char **map_array, int x_cord, int y_cord)
{
	t_cords	cords;

	cords.x = x_cord - 1;
	cords.y = y_cord - 1;
	while (map_array[++cords.x])
	{
		while (map_array[cords.x][++cords.y])
		{
			if (in_group(map_array[cords.x][cords.y], PLAYER_VALID))
			{
				break ;
			}
		}
		if (in_group(map_array[cords.x][cords.y], PLAYER_VALID))
		{
			break ;
		}
		cords.y = -1;
	}
	if (cords.y == -1)
	{
		cords.y++;
	}
	return (cords);
}
