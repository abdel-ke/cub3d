/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 09:58:25 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 19:40:01 by abdel-ke         ###   ########.fr       */
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

int		iswallat(int x, int y)
{
	int mapx;
	int mapy;

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
	double new_p_y;

	d->p.rot_an += d->p.turn_dir * d->p.rot_spd;
	if (d->p.walk_dir != 0)
	{
		mv_stp = d->p.walk_dir * d->p.mv_spd;
		new_p_x = d->p.pl_x + cos(d->p.rot_an) * mv_stp;
		new_p_y = d->p.pl_y + sin(d->p.rot_an) * mv_stp;
	}
	if (d->p.st_side != 0)
	{
		mv_stp1 = d->p.st_side * d->p.mv_spd;
		new_p_x = d->p.pl_x + cos(d->p.rot_an - (90 * M_PI / 180)) * mv_stp1;
		new_p_y = d->p.pl_y + sin(d->p.rot_an - (90 * M_PI / 180)) * mv_stp1;
	}
	if (!iswallat(d->p.pl_x, new_p_y))
		d->p.pl_y = new_p_y;
	if (!iswallat(new_p_x, d->p.pl_y))
		d->p.pl_x = new_p_x;
}

void	put_player(t_data *d, int i, int j, double rotation)
{
	d->p.rot_an = rotation;
	d->p.pl_y = i * TILE_SIZE + TILE_SIZE / 2;
	d->p.pl_x = j * TILE_SIZE + TILE_SIZE / 2;
}

int		draw(t_data *d)
{
	mlx_destroy_image(d->mlx.mlx_ptr, d->load_img);
	d->load_img = mlx_new_image(d->mlx.mlx_ptr, d->win_w, d->win_h);
	update_player(d);
	sky_floor_color(d);
	castAllRays(d);
	draw_map(d);
	mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr, d->load_img, 0, 0);
	return (0);
}
