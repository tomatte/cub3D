/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 00:04:13 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/19 01:39:54 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_tf	validate_map(char **map_array)
{
	if (!player_locator(map_array))
	{
		return (print_error(E_MORE_PLAYERS));
	}
	cleanup_map_first(map_array);
	if (!map_chars_validation(map_array))
	{
		return (print_error(E_MAP_CHARS_INVALID));
	}
	map_outline(map_array);
	map_nu_walls(map_array);
	if (!stuck_player(map_array))
	{
		return (print_error(E_MAP_WALLS_OUTER));
	}
	outer_edge_removal(map_array);
	if (!geom_inner_sealed(map_array))
	{
		return (print_error(E_MAP_WALLS_INNER));
	}
	change_cha_array(map_array, "1", "@");
	return (TRUE);
}

t_tf	player_locator(char **map_array)
{
	int	counter_line;
	int	counter_collum;
	int	player_q;

	counter_line = -1;
	counter_collum = -1;
	player_q = 0;
	while (map_array[++counter_line])
	{
		while (map_array[counter_line][++counter_collum])
		{
			if (in_group(map_array[counter_line][counter_collum], \
						PLAYER_VALID))
			{
				player_q++;
			}
		counter_collum = -1;
		}
	}
	if (player_q != 1)
	{
		return (FALSE);
	}
	return (TRUE);
}

void	cleanup_map_first(char **map_array)
{
	int		counter_1;
	int		counter_2;

	counter_1 = -1;
	counter_2 = -1;
	while (map_array[++counter_1])
	{
		while (map_array[counter_1][++counter_2])
		{
			if (map_array[counter_1][counter_2] == '1' && \
					!adjacent_to_char(map_array, counter_1, counter_2, '0')
					&& (adjacent_to_char(map_array, counter_1, \
						counter_2, 'E') == FALSE
					&& adjacent_to_char(map_array, counter_1, \
						counter_2, 'W') == FALSE
					&& adjacent_to_char(map_array, counter_1, \
						counter_2, 'S') == FALSE
					&& adjacent_to_char(map_array, counter_1, \
						counter_2, 'N') == FALSE))
			{
				map_array[counter_1][counter_2] = ' ';
			}
		}
		counter_2 = -1;
	}
}

t_tf	adjacent_to_char(char **map_ar, int x_cord, int y_cord, char cha)
{
	if ((x_cord > 0 && y_cord > 0 && map_ar[x_cord - 1][y_cord - 1] == cha)
		|| (y_cord > 0 && map_ar[x_cord][y_cord - 1] == cha)
		|| (map_ar[x_cord + 1] && y_cord > 0 && \
			map_ar[x_cord + 1][y_cord - 1] == cha)
		|| (x_cord > 0 && map_ar[x_cord - 1][y_cord] == cha)
		|| (map_ar[x_cord + 1] && map_ar[x_cord + 1][y_cord] == cha)
		|| (x_cord > 0 && map_ar[x_cord - 1][y_cord + 1] == cha)
		|| map_ar[x_cord][y_cord + 1] == cha
		|| (map_ar[x_cord + 1] && map_ar[x_cord + 1][y_cord + 1] == cha))
	{
		return (TRUE);
	}
	return (FALSE);
}

t_tf	map_chars_validation(char **map_array)
{
	int	lines;
	int	collums;

	lines = -1;
	collums = -1;
	while (map_array[++lines])
	{
		while (map_array[lines][++collums])
		{
			if (!in_group(map_array[lines][collums], MAP_CHARS_VALID))
			{
				return (FALSE);
			}
		collums = -1;
		}
	}
	return (TRUE);
}
