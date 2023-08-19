/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:15:41 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/20 22:26:32 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	close_x(t_mlx *mlx)
{
	ft_printf("\nProgram closed.\n");
	destroy_mlx(mlx);
	return (0);
}

void	close_window_x(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 1L << 17, close_x, mlx);
}
