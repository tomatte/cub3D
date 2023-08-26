/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/26 17:07:08 by suzy             ###   ########.fr       */
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
	char	*t1 = "book.xpm";
	char	*t2 = "bricks.xpm";
	char	*t3 = "wet_sponge.xpm";
	char	*t4 = "wall_3.xpm";

	init_texture_image(mlx, &mlx->textures[0], t1);
	init_texture_image(mlx, &mlx->textures[1], t2);
	init_texture_image(mlx, &mlx->textures[2], t3);
	init_texture_image(mlx, &mlx->textures[3], t4);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	(void) argc;
	(void) argv;
	init_minilibx(&mlx);
	init_hooks(&mlx);
	init_textures(&mlx);
	mlx_loop_hook(mlx.mlx, keep_drawing, &mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
