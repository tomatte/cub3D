/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:40:19 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/02 18:38:38 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libs/libft/includes/libftprintf.h"
# include <mlx.h>

//screen
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 720

//keys
# define ESC_KEY 65307
# define ARROW_LEFT 65361
# define ARROW_UP 65362
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364

//colors
# define RED 0x00FF0000
# define DEFAULT_COLOR 0x000000FF

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_line
{
	int	x;
	int	y;
	int	x2;
	int	y2;
	int	w;
	int	h;
	int	dx1;
	int	dy1;
	int	dx2;
	int	dy2;
	int	longest;
	int	shortest;
	int	proportion;
	int	color;
}	t_line;

//minilibx
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	init_minilibx(t_mlx *mlx);
void	destroy_mlx(t_mlx *mlx);
void	put_image(t_mlx *mlx);

//line
void	asign_values(t_line *line);
void	draw_line(t_mlx *mlx, t_line line);
void	draw_line2(t_mlx *mlx, t_line line, int color);
t_line	points(int x, int y, int x2, int y2);

//hooks
void	init_hooks(t_mlx *mlx);
void	close_window_x(t_mlx *mlx);


//playground
void	playground(t_mlx *mlx);

#endif
