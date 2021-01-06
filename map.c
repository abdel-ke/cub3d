/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:10:09 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/06 18:55:53 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ddaa(t_data *d, int x1, int y1)
{
	int i;

	i = 0;
	d->dda.dx = x1 - d->p.pl_x * MINI_MAP;
	d->dda.dy = y1 - d->p.pl_y * MINI_MAP;
	d->dda.steps = abs(d->dda.dx) > abs(d->dda.dy) ?
	abs(d->dda.dx) : abs(d->dda.dy);
	d->dda.Xinc = d->dda.dx / (float)d->dda.steps;
	d->dda.Yinc = d->dda.dy / (float)d->dda.steps;
	d->dda.X = d->p.pl_x * MINI_MAP;
	d->dda.Y = d->p.pl_y * MINI_MAP;
	while (i <= d->dda.steps)
	{
		d->load_data[(int)d->dda.Y * d->win_w + (int)d->dda.X] = 0xf00f0f;
		d->dda.X += d->dda.Xinc;
		d->dda.Y += d->dda.Yinc;
		i++;
	}
}

void	circle(t_data *d, int tile_x, int tile_y)
{
	double a;
	double x;
	double y;

	a = 0;
	while (a <= M_PI * 2)
	{
		x = d->p.rad * cos(a) + tile_x * MINI_MAP;
		y = d->p.rad * sin(a) + tile_y * MINI_MAP;
		mlx_pixel_put(d->mlx.mlx_ptr, d->mlx.win_ptr, x, y, 0xff00ff);
		a += 0.01;
	}
}

void	square(t_data *t, int tile_x, int tile_y)
{
	int x;
	int y;

	x = 0;
	while (x <= TILE_SIZE * MINI_MAP)
	{
		y = 0;
		while (y <= TILE_SIZE * MINI_MAP)
		{
			t->load_data[(tile_y + y) * t->win_w + (tile_x + x)] = 0x0000ff;
			y++;
		}
		x++;
	}
}

void	draw_map(t_data *t)
{
	int i;
	int j;
	int tile_x;
	int tile_y;

	i = 0;
	while (i < t->parse.map.nbr_rows)
	{
		j = 0;
		while (j < t->parse.map.nbr_cols)
		{
			tile_x = j * TILE_SIZE * MINI_MAP;
			tile_y = i * TILE_SIZE * MINI_MAP;
			// if (map[i][j] == '1')
			if (t->parse.map.map[i][j] == '1')
				square(t, (int)tile_x, (int)tile_y);
			j++;
		}
		i++;
	}
	circle(t, t->p.pl_x, t->p.pl_y);
}

int		draw(t_data *d)
{
	mlx_destroy_image(d->mlx.mlx_ptr, d->load_img);
	d->load_img = mlx_new_image(d->mlx.mlx_ptr, d->win_w, d->win_h);
	update_player(d);
	sky_floor_color(d);
	castallrays(d);
	draw_map(d);
	mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr, d->load_img, 0, 0);
	return (0);
}
