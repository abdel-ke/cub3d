/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 09:58:25 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 11:00:43 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	initial_player(t_data *d)
{
	d->p.rad = TILE_SIZE * 10 / 100 * MINI_MAP;
	d->win_w = 1080;
	d->win_h = 920;
	d->num_rays = d->win_w / WALL_STRIP_WIDTH;
	d->p.rot_an = M_PI;
	d->p.mv_spd = 5.0;
	d->p.rot_spd = 2 * (M_PI / 180);
	d->nbr_spr = 0;
	d->r_cst.dist_ray = (int *)malloc(sizeof(d->r_cst.dist_ray) * d->win_w);
	find_player(d);
}

void	ddaa(t_data *d, int X0, int Y0, int X1, int Y1)
{
	d->dda.dx = X1 - X0;
	d->dda.dy = Y1 - Y0;
	d->dda.steps = abs(d->dda.dx) > abs(d->dda.dy) ?
	abs(d->dda.dx) : abs(d->dda.dy);
	d->dda.Xinc = d->dda.dx / (float)d->dda.steps;
	d->dda.Yinc = d->dda.dy / (float)d->dda.steps;
	d->dda.X = X0;
	d->dda.Y = Y0;
	for (int i = 0; i <= d->dda.steps; i++)
	{
		d->load_data[(int)d->dda.Y * d->win_w + (int)d->dda.X] = 0xf00f0f;
		d->dda.X += d->dda.Xinc;
		d->dda.Y += d->dda.Yinc;
	}
}

int		isWallAt(int x, int y)
{
	int mapx, mapy;
	mapx = x / TILE_SIZE;
	mapy = y / TILE_SIZE;
	if (map[mapy][mapx] == '1')
		return (1);
	if (map[mapy][mapx] == '2')
		return (2);
	return (0);
}

void	update_player(t_data *d)
{
	double mv_stp;
	double mv_stp1;
	double new_p_x;
	double new_P_y;

	d->p.rot_an += d->p.turn_dir * d->p.rot_spd;
	if (d->p.walk_dir != 0)
	{
		mv_stp = d->p.walk_dir * d->p.mv_spd;
		new_p_x = d->p.pl_x + cos(d->p.rot_an) * mv_stp;
		new_P_y = d->p.pl_y + sin(d->p.rot_an) * mv_stp;
	}
	if (d->p.st_side != 0)
	{
		mv_stp1 = d->p.st_side * d->p.mv_spd;
		new_p_x = d->p.pl_x + cos(d->p.rot_an - (90 * M_PI / 180)) * mv_stp1;
		new_P_y = d->p.pl_y + sin(d->p.rot_an - (90 * M_PI / 180)) * mv_stp1;
	}
	if (!isWallAt(d->p.pl_x, new_P_y))
		d->p.pl_y = new_P_y;
	if (!isWallAt(new_p_x, d->p.pl_y))
		d->p.pl_x = new_p_x;
}

void	circle(t_data *d, int tileX, int tileY)
{
	double a;
	double x;
	double y;

	a = 0;
	while (a <= M_PI * 2)
	{
		x = d->p.rad * cos(a) + tileX * MINI_MAP;
		y = d->p.rad * sin(a) + tileY * MINI_MAP;
		mlx_pixel_put(d->mlx.mlx_ptr, d->mlx.win_ptr, x, y, 0xff00ff);
		a += 0.01;
	}
}

int		keyPressed(int key, t_data *d)
{
	d->p.walk_dir = 0;
	d->p.turn_dir = 0;
	d->p.st_side = 0;
	if (key == UP_KEY)
		d->p.walk_dir = 1;
	if (key == DOWN_KEY)
		d->p.walk_dir = -1;
	if (key == RIGHT_KEY)
		d->p.turn_dir = 1;
	if (key == LEFT_KEY)
		d->p.turn_dir = -1;
	if (key == A_KEY)
		d->p.st_side = +1;
	if (key == D_KEY)
		d->p.st_side = -1;
	if (key == QUIT_KEY)
		exit(0);
	return (0);
}

int		keyRealease(int key, t_data *d)
{
	if (key == UP_KEY)
		d->p.walk_dir = 0;
	if (key == DOWN_KEY)
		d->p.walk_dir = 0;
	if (key == RIGHT_KEY)
		d->p.turn_dir = 0;
	if (key == LEFT_KEY)
		d->p.turn_dir = 0;
	if (key == A_KEY)
		d->p.st_side = 0;
	if (key == D_KEY)
		d->p.st_side = 0;
	return (0);
}

void	put_player(t_data *d, int i, int j, double rotation)
{
	d->p.rot_an = rotation;
	d->p.pl_y = i * TILE_SIZE + TILE_SIZE / 2;
	d->p.pl_x = j * TILE_SIZE + TILE_SIZE / 2;
}

void	find_player(t_data *d)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == 'N')
				put_player(d, i, j, 3 * M_PI / 2);
			else if (map[i][j] == 'W')
				put_player(d, i, j, M_PI);
			else if (map[i][j] == 'E')
				put_player(d, i, j, 0);
			else if (map[i][j] == 'S')
				put_player(d, i, j, M_PI / 2);
			else if (map[i][j] == '2')
				d->nbr_spr++;
			j++;
		}
		i++;
	}
	stock_pos_spr(d);
}

void	sky_floor_color(t_data *d)
{
	int x;
	int y;

	x = d->win_h / 2 * d->win_w;
	y = 0;
	while (y != x)
	{
		d->load_data[y] = 0x99ccff;
		d->load_data[x + y++] = 0xcd8500;
	}
}

int		Draw(t_data *d)
{
	mlx_destroy_image(d->mlx.mlx_ptr, d->load_img);
	// mlx_clear_window(d->mlx.mlx_ptr, d->mlx.img_ptr);
	d->load_img = mlx_new_image(d->mlx.mlx_ptr, d->win_w, d->win_h);
	// mlx_clear_window(d->mlx.mlx_ptr, d->mlx.win_ptr);
	update_player(d);
	sky_floor_color(d);
	castAllRays(d);
	draw_map(d);
	mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr, d->load_img, 0, 0);
	return 0;
}
