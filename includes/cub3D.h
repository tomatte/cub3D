/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:19 by dbrandao          #+#    #+#             */
/*   Updated: 2023/06/27 19:50:00 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libftprintf.h"
# include <mlx.h>

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

//minilibx
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	init_minilibx(t_mlx *mlx);
void	destroy_mlx(t_mlx *mlx);

#endif
