/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:14:08 by suzy              #+#    #+#             */
/*   Updated: 2023/08/24 04:42:30 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

const int map[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	calc_next_column_values(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (looking_left(r->angle))
		r->column_x = backward_square(r->x);
	else
		r->column_x = foward_square(r->x);
	r->rdx_col = r->column_x - r->x;
	r->rdy_col = get_rdy(r->rdx_col, r->angle);
	r->column_y = r->y + r->rdy_col;
}

void	calc_next_row_values(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (looking_up(r->angle))
		r->row_y = backward_square(r->y);
	else
		r->row_y = foward_square(r->y);
	r->rdy_row = r->row_y - r->y;
	r->rdx_row = get_rdx(r->rdy_row, r->angle);
	r->row_x = r->x + r->rdx_row;
}

double	get_distance(double old_x, double old_y, double x, double y)
{
	double	h;

	h = sqrt(pow(positive(x - old_x), 2) + pow(positive(y - old_y), 2));
	return (h);
}

int	is_border_north(t_mlx *mlx)
{
	
}

static void	fix_base_border(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	double	diff_y;

	diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	if (!is_wall(mlx) || diff_y >= 1)
		return ;
	if (!has_floats(r->x))
	{
		r->x = r->row_x;
		r->y = r->row_y;
		r->is_base_x = 0;
		return ;
	}
}

static void	fix_base_border2(t_mlx *mlx)
{
	t_ray	*r;
	int		x;
	int		y;

	r = &mlx->ray;
	if (!is_wall(mlx))
		return ;
	if (has_floats(r->y))
		return ;
/* 	if ((int) r->column_x % TILE_SIZE > 4 && (int) r->column_x % TILE_SIZE < 60)
		return ;
	if ((int) r->column_y % TILE_SIZE > 1 && (int) r->column_y % TILE_SIZE < 63)
		return ; */
	if (looking_left(r->angle))
		x = (int)(r->x / TILE_SIZE);
	else
		x = (int)(ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int)(r->y / TILE_SIZE);
	else
		y = (int)(ceil(r->y) / TILE_SIZE);
	//printf("master_x: %lf  |  master_y: %lf\n", mlx->old_ray.x, mlx->old_ray.y);
	printf("master_map_x: %d  |  master_map_y: %d\n", mlx->old_ray.map_x, mlx->old_ray.map_y);
	printf("current_map_x: %d  |  current_map_y: %d\n", r->map_x, r->map_y);
	if (mlx->old_ray.map_x != r->map_x)
		return ;
	if (ft_abs(mlx->old_ray.map_y - r->map_y) <= 1)
	{
		if (mlx->old_ray.is_base_x)
		{
			r->x = r->column_x;
			r->y = r->column_y;
			r->is_base_x = 1;
		}
		else
		{
			r->x = r->row_x;
			r->y = r->row_y;
			r->is_base_x = 0;
		}
	}

}

/* 
	ao inves de salvar cada raio novo
	salvar apenas um raio do bloco que com certeza não está em uma quina
	se o proximo raio aumentar apenas um bloco na mesma linha, entao tem q manter a base

	ex: map[1, 1] == base_x, then map[2, 1] == base_x, then map[3,1] == base_x
 */
void	save_block_position(t_mlx *mlx)
{
	int	x;
	int	y;
	t_ray *r;
	r = &mlx->ray;
	if (!is_wall(mlx))
		return ;
	if (!is_east(r->x, r->y) && !is_west(r->x, r->y))
		return ;
	if ((int) r->column_y % TILE_SIZE < 2 || (int) r->column_y % TILE_SIZE >= 62)
		return ;
	if (looking_left(r->angle))
		x = (int)(r->x / TILE_SIZE);
	else
		x = (int)(ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int)(r->y / TILE_SIZE);
	else
		y = (int)(ceil(r->y) / TILE_SIZE);
	mlx->block_x = x;
	mlx->block_y = y;
	mlx->old_ray = mlx->ray;
}

void	jump_to_next_square(t_mlx *mlx)
{
	t_ray	*r;
	double	col_pixels;
	double	row_pixels;
	double	col_distance;
	double	row_distance;

	r = &mlx->ray;
	col_pixels = positive((r->column_x + r->column_y) - (r->x + r->y));
	row_pixels = positive((r->row_x + r->row_y) - (r->x + r->y));
	col_distance = get_distance(r->x, r->y, r->column_x, r->column_y);
	row_distance = get_distance(r->x, r->y, r->row_x, r->row_y);
 	if (col_pixels < row_pixels || r->rdy_col == 0)
	{
		r->x = r->column_x;
		r->y = r->column_y;
		r->is_base_x = 1;
	}
	else
	{
		r->x = r->row_x;
		r->y = r->row_y;
		r->is_base_x = 0;
	}
	save_block_position(mlx);
	fix_base_border(mlx);
	fix_base_border2(mlx);
	//fix_base_y_border(mlx);
}

int	is_wall(t_mlx *mlx)
{
	t_ray	*r;
	int		x;
	int		y;

	r = &mlx->ray;
	if (looking_left(r->angle))
		x = (int)(r->x / TILE_SIZE);
	else
		x = (int)(ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int)(r->y / TILE_SIZE);
	else
		y = (int)(ceil(r->y) / TILE_SIZE);
	if (map[y][x] == 1)
	{
		r->map_x = x;
		r->map_y = y;
	}
	return (map[y][x]);
}

int	is_old_wall(double angle, double old_x, double old_y)
{
	int		x;
	int		y;

	if (looking_left(angle))
		x = (int)(old_x / TILE_SIZE);
	else
		x = (int)(ceil(old_x) / TILE_SIZE);
	if (looking_up(angle))
		y = (int)(old_y / TILE_SIZE);
	else
		y = (int)(ceil(old_y) / TILE_SIZE);
	return (map[y][x]);
}

int	is_debug(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	if (!is_wall(mlx))
		return (0);
	if (mlx->texture_selected == WEST || mlx->texture_selected == EAST)
		return (0);
	if (is_wall(mlx) && ((r->y >= 127 && r->y < 128.5) || (r->y >= 191 && r->y < 192.5)))
		return (1);
	return (0);
}

void debug1(t_mlx *mlx, int show, int index)
{
	t_ray	*r;
	static double	old_x;
	static double	old_y;
	static int		old_index;
	static double	before_row_rdx;
	static double	before_row_rdy;
	static double	before_col_rdx;
	static double	before_col_rdy;
	static double	old_row_y;
	static double	old_row_x;
	static double	old_column_y;
	static double	old_column_x;

	r = &mlx->ray;
	if (show && is_debug(mlx))
	{
		printf("rx: %lf  |  ry: %lf\n", r->x, r->y);
		printf("before_x: %lf  |  before_y: %lf  |  is_old_wall: %d  |  is_wall: %d  |  old_index: %d  |  index: %d\n", old_x, old_y, is_old_wall(r->angle, old_x, old_y), is_wall(mlx), old_index, index);
		printf("old_rdx_row: %lf  |  old_rdy_row: %lf\n", before_row_rdx, before_row_rdy);
		printf("old_rdx_row: %lf  |  old_rdy_row: %lf\n", before_col_rdx, before_col_rdy);
		printf("old_row_x: %lf  |  old_row_y: %lf\n", old_row_x, old_row_y);
		printf("old_column_x: %lf  |  old_column_y: %lf\n", old_column_x, old_column_y);
		return ;
	}
	old_x = r->x;
	old_y = r->y;
	old_index = index;
	before_row_rdx = r->rdx_row;
	before_row_rdy = r->rdy_row;
	before_col_rdx = r->rdx_col;
	before_col_rdy = r->rdy_col;
	old_row_y = r->row_y;
	old_row_x = r->row_x;
	old_column_y = r->column_y;
	old_column_x = r->column_x;
}

static void	debug2(t_mlx *mlx)
{
	t_ray	*r;
	double test_col;
	double test_row;
	double	diff;
	double	diff_y;
	double	diff_x;

	r = &mlx->ray;
	test_col = positive(r->rdx_col) + positive(r->rdy_col);
	test_row = positive(r->rdx_row) + positive(r->rdy_row);
	diff = positive(test_col - test_row);
	diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	diff_x = positive(positive(r->rdx_col) - positive(r->rdx_row));
	if (is_debug(mlx))
	{
		printf("rdy_row: %lf  |  rdx_row: %lf\n", r->rdy_row, r->rdx_row);
		printf("rdy_col: %lf  |  rdx_col: %lf\n", r->rdy_col, r->rdx_col);
		printf("column_x: %lf  |  column_y: %lf\n", r->column_x, r->column_y);
		printf("row_x: %lf  |  row_y: %lf\n", r->row_x, r->row_y);
		printf("test_col: %lf  |  test_row: %lf\n", test_col, test_row);
		printf("diff: %lf  |  diff_y: %lf  |  diff_x: %lf\n", diff, diff_y, diff_x);
		printf("angle: %lf\n", r->angle);
		int txtr = mlx->texture_selected;
		printf("Texture selected: %s\n", txtr == NORTH ? "North" : txtr == SOUTH ? "South" : txtr == WEST ? "West" : "East");
		printf("blox_x: %d  |  block_y: %d\n", mlx->block_x, mlx->block_y);
		//printf("--------------------------------------------------------\n");
	}
}

void	print_wall(t_mlx *mlx)
{
	int	x;
	int	y;
	t_ray	*r;

	r = &mlx->ray;
	if (looking_left(r->angle))
		x = (int)(r->x / TILE_SIZE);
	else
		x = (int)(ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int)(r->y / TILE_SIZE);
	else
		y = (int)(ceil(r->y) / TILE_SIZE);
	printf("map[y:%d][x:%d] == %d\n", y, x, map[y][x]);
}

void	debug3(t_mlx *mlx)
{
	t_ray	*r;
	double	col_pixels;
	double	row_pixels;
	double	col_distance;
	double	row_distance;

	r = &mlx->ray;
	col_pixels = positive(r->rdx_col) + positive(r->rdy_col);
	row_pixels = positive(r->rdx_row) + positive(r->rdy_row);
	col_distance = get_distance(r->x, r->y, r->column_x, r->column_y);
	row_distance = get_distance(r->x, r->y, r->row_x, r->row_y);
	static double max_dist = 0;
	static double max_diff_y = 0;
	static double max_diff_x = 0;
	double distance_diff = positive(col_distance - row_distance);
	double diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	double diff_x = positive(positive(r->rdx_col) - positive(r->rdx_row));
	if (mlx->texture_selected == WEST || mlx->texture_selected == EAST)
		return ;
	if (is_debug(mlx))
	{
		if (distance_diff > max_dist)
			max_dist = distance_diff;
		if (diff_y > max_diff_y)
			max_diff_y = diff_y;
		if (diff_x > max_diff_x)
			max_diff_x = diff_x;
		printf("column_x: %lf  |  column_y: %lf  |  row_x: %lf  |  row_y: %lf\n", r->column_x, r->column_y, r->row_x, r->row_y);
		printf("col_distance: %lf  |  row_distance: %lf  |  is_base_x: %lf\n", col_distance, row_distance, r->is_base_x);
		printf("col_pixels: %lf  |  row_pixels: %lf  |  pixels_diff: %lf\n", col_pixels, row_pixels, positive(col_pixels - row_pixels));
		printf("distance diff: %lf  |  max_dist: %lf  |  max_diff_y: %lf  |  max_diff_x: %lf\n", distance_diff, max_dist, max_diff_y, max_diff_x);
		print_wall(mlx);
/* 	static double max_x_remainder = 0;
	static double max_y_remainder = 0;
	if () */
		printf("x_remainder: %d  |  y_remainder: %d\n", (int) r->x % TILE_SIZE, (int) r->y % TILE_SIZE);
		printf("col_x_remainder: %d  |  col_y_remainder: %d\n", (int) r->column_x % TILE_SIZE, (int) r->column_y % TILE_SIZE);
		printf("---------------------------------------------------------\n");
	}
}

int	is_limit(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	if (r->x <= 0 || r->y <= 0)
		return (1);
	if (r->x >= SCREEN_WIDTH || r->y >= SCREEN_HEIGHT)
		return (1);
	return (0);
}

void	dda_ray(t_mlx *mlx)
{
	t_ray	*r;
	int		i;
	double test_col;
	double test_row;

	r = &mlx->ray;
	r->x = mlx->player.x;
	r->y = mlx->player.y;
	i = 0;
	while (i++ < 100)
	{
		calc_next_column_values(mlx);
		calc_next_row_values(mlx);
		jump_to_next_square(mlx);
		if (is_wall(mlx) || is_limit(mlx))
		{
			select_texture(mlx);
			debug1(mlx, 1, i);
			debug2(mlx);
			debug3(mlx);
			//previous_corner_pixel(mlx);
			break ;
		}
		else
		{
			debug1(mlx, 0, i);
		}
	}
}

/*  
	verificar 1 pixel anterior e um 1 pixel posterior da quina

	ao chegar um pixel anterior à quina, salvar dados do raio
	ao chegar em uma quina e detectar uma textura diferente, salvar essa informação
	ao chegar em um pixel posterior à quina, verificar:
		tem a mesma textura que a do raio salvo
		a textura da quina está diferente desses dois raios
	então voltar o grau da quina e forçar a base correta

	para fazer isso a variavel "sum" pode ser parte da struct ml
	e o index do raio tambem pode se tornar parte da struct, pois ele tem q ser reduzido tbm
	basta ela ser alterada para o raio desejado e pronto, o codigo continua

*/

void	previous_corner_pixel(t_mlx *mlx)
{
	t_ray	*r;
	int		y;

	r = &mlx->ray;
	if (!is_east(r->x, r->y))
		return ;
	y = (int) r->y;
	if ((y + 2) % TILE_SIZE == 0)
	{
		printf("x: %lf  |  y: %lf\n", r->x, r->y);
	}
	if (y > 150 && (y - 1) % TILE_SIZE == 0)
	{
			printf("x: %lf  |  y: %lf\n", r->x, r->y);
			exit(0);
	}
}