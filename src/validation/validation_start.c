/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:29:49 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/28 21:45:45 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_tf	validation(t_game_data *game_data, int argc, char **argv)
{
	init_parameters(&game_data->parameters);
	if (!validate_args(game_data, argc, argv))
		return (fail_validation(&game_data->parameters, NULL));
	game_data->map_data = get_array_map(open(argv[1], O_RDONLY));
	if (!game_data->map_data)
	{
		printf(E_MAP_EMPTY);
		return (fail_validation(&game_data->parameters, NULL));
	}
	if (!validate_files(&game_data->parameters, argv[1]))
		return (fail_validation(&game_data->parameters, game_data->map_data));
	if (!validate_map(game_data->map_data))
		return (fail_validation(&game_data->parameters, game_data->map_data));
	game_data->map_dev = get_array_map(open(argv[1], O_RDONLY));
	cleanup_map_first(game_data->map_dev);
	return (TRUE);
}

t_tf	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	return (FALSE);
}

void	init_parameters(t_parameters *parameters)
{
	parameters->top_color = -1;
	parameters->bottom_color = -1;
	parameters->east = NULL;
	parameters->north = NULL;
	parameters->south = NULL;
	parameters->west = NULL;
}

t_tf	validate_args(t_game_data *game_data, int argc, char **argv)
{
	int	holder;

	if (argc < 2)
		return (print_error(E_NO_MAP));
	if (argc > 2)
		return (print_error(E_MORE_MAP));
	if (validate_map_name(game_data, argv[1]) == FALSE)
		return (print_error(E_MAP_EXTENSION));
	holder = open(argv[1], O_RDONLY);
	if (holder == -1)
		return (print_error(E_MAP_INVALID));
	close(holder);
	return (TRUE);
}

t_tf	validate_map_name(t_game_data *game_data, char *name_map)
{
	char	*dot_holder;

	(void)game_data;
	dot_holder = ft_strrchr(name_map, '.');
	if (!dot_holder)
		return (FALSE);
	if (ft_strncmp(dot_holder, ".cub", ft_strlen(dot_holder)) || \
						ft_strncmp(".cub", dot_holder, 4))
	{
		printf(E_MAP_NAME_INVALID, name_map);
		return (FALSE);
	}
	return (TRUE);
}
