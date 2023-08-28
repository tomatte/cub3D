/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 13:22:18 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static	void	fill_texture_colors(t_texture *texture)
{
	int	*aux;
	int	i;
	int	j;

	texture->colors = ft_calloc(texture->height + 1, sizeof(int ***));
	i = -1;
	while (++i < texture->height)
		texture->colors[i] = ft_calloc(texture->width + 1, sizeof(int **));
	texture->colors[texture->height] = NULL;
	aux = texture->addr;
	i = -1;
	while (texture->colors[++i])
	{
		j = -1;
		while (++j < texture->width)
			texture->colors[i][j] = aux++;
		texture->colors[i][j] = NULL;
	}
}

void	init_texture_image(t_mlx *mlx, t_texture *texture, char *str)
{
	int			aux;

	texture->img = mlx_xpm_file_to_image(
			mlx->mlx,
			str,
			&texture->width,
			&texture->height
			);
	texture->addr = (int *) mlx_get_data_addr(
			texture->img,
			&aux,
			&aux,
			&aux);
	fill_texture_colors(texture);
}

static void	init_textures(t_mlx *mlx)
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	north = mlx->game_data.parameters.north;
	south = mlx->game_data.parameters.south;
	east = mlx->game_data.parameters.east;
	west = mlx->game_data.parameters.west;
	init_texture_image(mlx, &mlx->textures[NORTH], north);
	init_texture_image(mlx, &mlx->textures[SOUTH], south);
	init_texture_image(mlx, &mlx->textures[EAST], east);
	init_texture_image(mlx, &mlx->textures[WEST], west);
}

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_game_data	game_data;

	if (validation(&game_data, argc, argv) == FALSE)
		exit(0);
	init_minilibx(&mlx);
	mlx.game_data = game_data;
	init_hooks(&mlx);
	init_textures(&mlx);
	init_player(&mlx);
	fill_map_sizes(&mlx.game_data);
	mlx_loop_hook(mlx.mlx, keep_drawing, &mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
