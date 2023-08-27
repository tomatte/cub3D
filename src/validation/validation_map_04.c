/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_04.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:19:46 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/19 00:34:57 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	change_cha_array(char **map_array, char *identify, char *substitute)
{
	int	counter;

	counter = -1;
	while (map_array[++counter])
	{
		change_cha_line(map_array[counter], identify, substitute);
	}
}

void	change_cha_line(char *map_line, char *identify, char *substitute)
{
	int		counter;
	int		index;

	if (!map_line || !identify || !substitute)
	{
		return ;
	}
	counter = -1;
	while (map_line[++counter])
	{
		index = in_identify(map_line[counter], identify);
		if (index == -1)
		{
			continue ;
		}
		map_line[counter] = substitute_find(substitute, index);
	}
}

int	in_identify(char cha_in_line, char *identify)
{
	int	counter;

	counter = -1;
	while (identify[++counter])
	{
		if (cha_in_line == identify[counter])
		{
			return (counter);
		}
	}
	return (-1);
}

char	substitute_find(char *substitute, int index)
{
	int	length;

	length = ft_strlen(substitute);
	if (index > length - 1)
	{
		return (substitute[length - 1]);
	}
	else
	{
		return (substitute[index]);
	}
}

void	outer_edge_removal(char **map_array)
{
	int	lines;
	int	collum;

	lines = -1;
	collum = -1;
	while (map_array[++lines])
	{
		while (map_array[lines][++collum] && \
				map_array[lines][collum] != OUTER_EDGE)
		{
			map_array[lines][collum] = ' ';
		}
		collum = ft_strlen(map_array[lines]);
		while (--collum >= 0 && map_array[lines][collum] != OUTER_EDGE)
		{
			map_array[lines][collum] = ' ';
		}
		collum = -1;
	}
}
