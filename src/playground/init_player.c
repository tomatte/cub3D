/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:07:50 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 23:33:01 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static char	*get_player_char(char *line)
{
	char	*c;

	c = ft_strchr(line, 'N');
	if (c == NULL)
		c = ft_strchr(line, 'S');
	if (c == NULL)
		c = ft_strchr(line, 'W');
	if (c == NULL)
		c = ft_strchr(line, 'E');
	return (c);
}

static void	init_player_position(t_mlx *mlx, char *a)
{
	char	*c;
	int		nx;
	int		ny;

	c = NULL;
	ny = 0;
	while (1)
	{
		c = get_player_char(mlx->game_data.map_data[ny]);
		if (c != NULL)
			break ;
		ny++;
	}
	nx = c - &mlx->game_data.map_data[ny][0];
	mlx->player.x = nx * TILE_SIZE + (TILE_SIZE / 2);
	mlx->player.y = ny * TILE_SIZE + (TILE_SIZE / 2);
	*a = *c;
}

static void	init_player_angle(t_mlx *mlx, char a)
{
	t_player	*p;

	p = &mlx->player;
	if (a == 'N')
		p->angle = PI + PI / 2;
	else if (a == 'S')
		p->angle = PI / 2;
	else if (a == 'W')
		p->angle = PI;
	else
		p->angle = 0;
}

void	init_player(t_mlx *mlx)
{
	char	a;

	init_player_position(mlx, &a);
	init_player_angle(mlx, a);
}
