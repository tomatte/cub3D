/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:44:31 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/28 22:20:52 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	string_size(char *string, char *cha_group)
{
	int	counter;

	counter = 0;
	while (*string)
	{
		if (!char_trim(*string++, cha_group))
		{
			counter++;
		}
	}
	return (counter);
}

int	char_trim(char cha, char const *cha_group)
{
	while (*cha_group)
	{
		if (cha == *cha_group)
		{
			return (1);
		}
		cha_group++;
	}
	return (0);
}

void	fill_map_sizes(t_game_data *game)
{
	int	lines;

	lines = 0;
	while (game->map_data[lines])
		lines++;
	game->line_length = ft_strlen(game->map_data[0]);
	game->map_lines = lines;
}

void	clear_map_arr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	clear_game_data(t_game_data *game_data)
{
	clear_map_arr(game_data->map_data);
	clear_map_arr(game_data->map_dev);
	free(game_data->parameters.east);
	free(game_data->parameters.west);
	free(game_data->parameters.north);
	free(game_data->parameters.south);
}
