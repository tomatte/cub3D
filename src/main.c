/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/02 14:35:05 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_texture_image(t_mlx *mlx)
{
	int		aux;

	mlx->texture_img = mlx_xpm_file_to_image(
			mlx->mlx,
			"./whatsapp-256.xpm",
			&mlx->texture_width,
			&mlx->texture_height
			);
	mlx->texture_addr = (int *) mlx_get_data_addr(
			mlx->texture_img,
			&aux,
			&aux,
			&aux);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	(void) argc;
	(void) argv;
	init_minilibx(&mlx);
	init_hooks(&mlx);
	init_texture_image(&mlx);
	mlx_loop_hook(mlx.mlx, keep_drawing, &mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
