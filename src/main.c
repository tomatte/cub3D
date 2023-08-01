/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/31 23:43:06 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_image_test(t_mlx *mlx)
{
	int		aux;
	int		i;
	int		j;

	mlx->texture_img = mlx_xpm_file_to_image(mlx->mlx, "./wall_3.xpm", &aux, &aux);
	mlx->texture_addr = mlx_get_data_addr(
			mlx->texture_img,
			&aux,
			&aux,
			&aux);
/* 	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			set_color(mlx->texture_addr[j + (i * 64)]);
			my_mlx_pixel_put(mlx, j, i);
		}
	}
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			set_color(mlx->texture_addr[j + (i * 64)]);
			my_mlx_pixel_put(mlx, j + 200, i + 200);
		}
	}

	put_image(mlx);
	mlx_loop(mlx->mlx); */
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	(void) argc;
	(void) argv;
	init_minilibx(&mlx);
	init_hooks(&mlx);
	init_image_test(&mlx);
	mlx_loop_hook(mlx.mlx, keep_drawing, &mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
