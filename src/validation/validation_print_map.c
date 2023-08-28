/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_print_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:30:12 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/28 22:20:45 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	map_print(char **data_map)
{
	int	line;
	int	collum;

	line = -1;
	collum = -1;
	while (data_map[++line])
	{
		while (data_map[line][++collum])
		{
			if (data_map[line][collum] == OUTER_EDGE)
			{
				printf("%c", data_map[line][collum]);
			}
			else if (data_map[line][collum] == ' ')
			{
				printf("%c", ' ');
			}
			else
			{
				printf("%c", data_map[line][collum]);
			}
		}
		printf("\n");
		collum = -1;
	}
}

void	map_print_with_colour(char **data_map)
{
	int	line;
	int	collum;

	line = -1;
	collum = -1;
	while (data_map[++line])
	{
		while (data_map[line][++collum])
		{
			if (data_map[line][collum] == OUTER_EDGE)
				printf("\e[42m%c\e[0m", data_map[line][collum]);
			else if (data_map[line][collum] == INNER_EDGE)
				printf("\e[44m%c\e[0m", data_map[line][collum]);
			else if (in_group(data_map[line][collum], "NSEW"))
				printf("\e[46m%c\e[0m", data_map[line][collum]);
			else if (data_map[line][collum] == ' ')
				printf("%c", ' ');
			else if (!in_group(data_map[line][collum], "01 NSEW"))
				printf("\e[45m%c\e[0m", data_map[line][collum]);
			else
				printf("\e[41m%c\e[0m", data_map[line][collum]);
		}
		printf("\n");
		collum = -1;
	}
}
