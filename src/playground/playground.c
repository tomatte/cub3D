/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/05 10:04:39 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	draw_direction_line(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	draw_line(
		mlx,
		points(
			round(p->x + P_SIZE / 2),
			round(p->y + P_SIZE / 2),
			round(p->x + (P_SIZE / 2) + (p->delta_x * 20)),
			round(p->y + (P_SIZE / 2) + (p->delta_y * 20))
			)
		);
}

void	draw_player(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	square2(mlx, (int) round(p->x), (int) round(p->y), P_SIZE);
	draw_direction_line(mlx);
}


static void	draw_rays(t_mlx *mlx)
{
	t_player	*p;
	t_ray		*r;
	int			i;
	int			aux;

	p = &mlx->player;
	r = &mlx->ray;
	set_color(0x0);
	draw_line(mlx, points(r->opx, r->opy, r->x, r->y));
	r->x = p->x * cos(p->angle) * 50;
	r->y = p->y * sin(p->angle) * 50;
	set_color(RED);
	aux = 0;
	i = 0;
	while (i++ < 2)
	{
		if (p->angle < PI)
		{
			aux = r->y + 63 - (int) r->y % 63;
			if (aux <= SCREEN_HEIGHT)
				r->y = aux;
		}
		else
		{
			aux = r->y - (int) (r->y) % 63;
			if (aux >= 0)
				r->y = aux;
		}
		if (p->angle > PI / 2 && p->angle < PI + PI / 2)
		{
			aux = r->x - (int) (r->x) % 63;
			if (aux >= 0)
				r->x = aux;
		}
		else
		{
			aux = r->x + 63 - (int) (r->x) % 63;
			if (aux <= SCREEN_WIDTH)
				r->x = aux;
		}
	}
	r->opx = p->x + P_SIZE / 2;
	r->opy = p->y + P_SIZE / 2;
	draw_line(mlx, points(p->x + P_SIZE / 2, p->y + P_SIZE / 2, r->x, r->y));
	set_color(DEFAULT_COLOR);
}

/*

	rate =  min(cos, sin) / max(cos, sin)

	x_greater = cos(a) > sin(a);
	rate = min(cos(a), sin(a)) / max(cos(a), sin(a);
	if (x_greater)
	{
		r->x += 63 - (int) (r->x) % 63;
		r->y = r->x * rate;
	}
	else
	{
		r->y += 63 - (int) (r->y) % 63;
		r->x = r->y * rate;
	}

 */

int	looking_up(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (p->angle > PI)
	{
		printf("looking up\n");
		return (1);
	}
	printf("looking down\n");
	return (0);
}

int	looking_left(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (p->angle > PI / 2 && p->angle < PI + PI / 2)
	{
		printf("looking left\n");
		return (1);
	}
	printf("looking right\n");
	return (0);
}

void	calc_delta_ray(t_mlx *mlx)
{
	t_ray		*r;
	int			jump_x;
	int			jump_y;

	r = &mlx->ray;
	if (looking_left(mlx))
		jump_x = (int) (r->x) % 63 * -1;
	else
		jump_x = 63 - (int) (r->x) % 63;
	if (looking_up(mlx))
		jump_y = (int) (r->y) % 63 * -1;
	else
		jump_y = 63 - (int) (r->y) % 63;
	if (jump_x < jump_y)
	{
		r->dx = jump_x;
		r->dy = jump_x * r->rate;
		if (looking_up(mlx) && r->dy > 0)
			r->dy *= -1;
		else if (!looking_up(mlx) && r->dy < 0)
			r->dy *= -1;
	}
	else
	{
		r->dy = jump_y;
		r->dx = jump_y * r->rate;
		if (looking_left(mlx) && r->dx > 0)
			r->dx *= -1;
		else if (!looking_left(mlx) && r->dx < 0)
			r->dx *= -1;
	}
}

double	get_rate(double angle)
{
	double	rate;

	rate = cos(angle) / sin(angle);
	return (rate);
}

void	test_case(t_mlx *mlx)
{
	t_player	*p;
	t_ray		*r;
	int			i = 0;

	p = &mlx->player;
	r = &mlx->ray;
	r->x = p->x;
	r->y = p->y;
	r->rate = get_rate(p->angle);
	while (i++ < 8)
	{
		calc_delta_ray(mlx);
		printf("dx: %lf, dy: %lf\n", r->dx, r->dy);
		r->x += r->dx;
		r->y += r->dy;
		if (r->x > SCREEN_WIDTH || r->y > SCREEN_HEIGHT || r->x < 0 || r->y < 0)
			break ;
		square2(mlx, (int) r->x - P_SIZE / 2, (int) r->y - P_SIZE / 2, P_SIZE);
	}
}

static void	erase_player(t_mlx *mlx)
{
	set_color(0x0);
	draw_player(mlx);
	test_case(mlx);
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	erase_player(mlx);
	update_player_position(mlx);
	draw_2d_blocks(mlx, 64);
	draw_player(mlx);
	test_case(mlx);
	//draw_rays(mlx);
	put_image(mlx);
	return (1);
}
