/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/27 10:01:25 by suzy             ###   ########.fr       */
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

static void	init_player_position(t_mlx *mlx)
{
	char	*c = NULL;
	int		nx;
	int		ny;

	ny = 0;
	printf("n: %s\n", c);
	while (1)
	{
		c  = ft_strchr(mlx->game_data.map_data[ny], 'N');
		if (c != NULL)
			break ;
		ny++;
	}
	printf("n: %d\n", c - &mlx->game_data.map_data[ny][0]);
	nx = c - &mlx->game_data.map_data[ny][0];
	mlx->player.x = nx * TILE_SIZE - (TILE_SIZE / 2);
	mlx->player.y = ny * TILE_SIZE - (TILE_SIZE / 2);
	printf("x: %lf\n", mlx->player.x);
	printf("y: %lf\n", mlx->player.y);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	init_minilibx(&mlx);
	if (validation(&(mlx.game_data), argc, argv) == FALSE)
		exit(0);
	init_hooks(&mlx);
	init_textures(&mlx);
	init_player_position(&mlx);
	mlx_loop_hook(mlx.mlx, keep_drawing, &mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
