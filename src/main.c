/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:25 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/10 13:56:40 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static	void	fill_texture_colors(t_mlx *mlx)
{
	int *aux;
	int	i;
	int	j;

	mlx->texture_colors = ft_calloc(mlx->texture_height + 1, sizeof(int ***));
	i = -1;
	while (++i < mlx->texture_height)
		mlx->texture_colors[i] = ft_calloc(mlx->texture_width + 1, sizeof(int **));
	mlx->texture_colors[mlx->texture_height] = NULL;
	aux = mlx->texture_addr;
	i = -1;
	while (mlx->texture_colors[++i])
	{
		j = -1;
		while (++j < mlx->texture_width)
			mlx->texture_colors[i][j]  = aux++;
		mlx->texture_colors[i][j] = NULL;
	}
}

void	init_texture_image(t_mlx *mlx,  char *str)
{
	int		aux;

	mlx->texture_img = mlx_xpm_file_to_image(
			mlx->mlx,
			str,
			&mlx->texture_width,
			&mlx->texture_height
			);
	mlx->texture_addr = (int *) mlx_get_data_addr(
			mlx->texture_img,
			&aux,
			&aux,
			&aux);
	fill_texture_colors(mlx);
	printf("img_width: %d  |  img_height: %d\n", mlx->texture_width, mlx->texture_height);
	//printf("color: %p\nverify: %p\n", mlx->texture_colors[0][mlx->texture_width - 1], (mlx->texture_addr + mlx->texture_width - 1)); exit(0);
}

static	void	fill_texture_color2(t_texture *texture)
{
	int *aux;
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
			texture->colors[i][j]  = aux++;
		texture->colors[i][j] = NULL;
	}
}

void	init_texture_image2(t_mlx *mlx,  char *str)
{
	t_texture	*texture;
	int			aux;

	texture = &mlx->texture;
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
	fill_texture_colors(mlx);
	printf("img_width: %d  |  img_height: %d\n", mlx->texture_width, mlx->texture_height);
	//printf("color: %p\nverify: %p\n", mlx->texture_colors[0][mlx->texture_width - 1], (mlx->texture_addr + mlx->texture_width - 1)); exit(0);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	(void) argc;
	(void) argv;
	init_minilibx(&mlx);
	init_hooks(&mlx);
	init_texture_image(&mlx, argv[1]);
	init_texture_image2(&mlx, argv[1]);
	mlx_loop_hook(mlx.mlx, keep_drawing, &mlx);
	mlx_loop(mlx.mlx);
	destroy_mlx(&mlx);
	return (0);
}
