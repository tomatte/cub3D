/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/26 18:47:18 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	draw_diagonal_line(t_mlx *mlx)
{
	draw_line(mlx, points(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	draw_line2(mlx, points(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT), RED);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_game_data    game_data;

	if (validation(&game_data, argc, argv) == FALSE)
	{
		exit(0);
	}

	(void) argc;
	(void) argv;
	init_minilibx(&mlx);
	draw_diagonal_line(&mlx);
	init_hooks(&mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
