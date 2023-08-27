/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:21:14 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/27 17:11:25 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > SCREEN_WIDTH)
		x = SCREEN_WIDTH;
	if (y > SCREEN_HEIGHT)
		y = SCREEN_HEIGHT;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *) dst = mlx->color;
}

void	init_minilibx(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->addr = mlx_get_data_addr(
			mlx->img,
			&mlx->bits_per_pixel,
			&mlx->line_length,
			&mlx->endian);
	mlx->color = DEFAULT_COLOR;
	init__color(&mlx->color);
	mlx->player.x = 100.0;
	mlx->player.y = 100.0;
}

void	clear_texture_colors(t_texture *texture)
{
	int			i;

	i = -1;
	while (++i <= texture->height)
		free(texture->colors[i]);
	free(texture->colors);
}

void	destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, mlx->textures[WEST].img);
	mlx_destroy_image(mlx->mlx, mlx->textures[EAST].img);
	mlx_destroy_image(mlx->mlx, mlx->textures[NORTH].img);
	mlx_destroy_image(mlx->mlx, mlx->textures[SOUTH].img);
	clear_texture_colors(&mlx->textures[NORTH]);
	clear_texture_colors(&mlx->textures[SOUTH]);
	clear_texture_colors(&mlx->textures[EAST]);
	clear_texture_colors(&mlx->textures[WEST]);
	clear_map_arr(mlx->game_data.map_data);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

void	put_image(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
