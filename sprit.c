/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:38:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/12 18:13:05 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	drow_strips(t_data *t, int s_x, int i, int x)
{
	int y;
	int xtext;
	int ytext;
	int start;
	int color;

	start = -1;
	y = 0;
	start = (t->parse.p_h / 2) - (t->spr->height / 2);
	t->spr->end = (t->parse.p_h / 2) + (t->spr->height / 2);
	if (start < 0)
	{
		y = -start;
		start = -1;
	}
	xtext = x * (64 / (double)t->spr->height);
	t->spr->end = t->spr->end > t->parse.p_h ? t->parse.p_h : t->spr->end;
	while (++start < t->spr->end)
	{
		ytext = y++ * (64 / (double)t->spr->height);
		color = t->spr->data_spr[ytext * 64 + xtext];
		if (t->r_cst.dist_ray[s_x] > t->spr[i].dist_x)
			if (color != 0x00000)
				t->load_data[start * t->parse.p_w + s_x] = color;
	}
}

void	drowsprite(t_data *d, int i)
{
	int x;

	x = 0;
	d->spr->height = (TILE_SIZE /
	d->spr[i].dist_x) * d->r_cst.distbprojectplane;
	d->spr->end = (d->parse.p_h / 2) + (d->spr->height / 2);
	d->spr->x_star_wind = (tan((FOV_ANGLE) / 2)
	* d->r_cst.distbprojectplane) + (tan(d->spr[i].spr_angle
	- d->p.rot_an) * d->r_cst.distbprojectplane)
	- (d->spr->height / 2);
	while (x < d->spr->height)
	{
		if (d->spr->x_star_wind >= 0 &&
		d->spr->x_star_wind < d->parse.p_w)
			drow_strips(d, d->spr->x_star_wind, i, x);
		x++;
		d->spr->x_star_wind++;
	}
}

void	draw_sprite(t_data *d, int count)
{
	int i;

	i = 0;
	d->p.rot_an = normalizeangle(d->p.rot_an);
	while (i < count)
	{
		found_spr_angle(d, i);
		if (sprite_visible(d, i) == 1)
			drowsprite(d, i);
		i++;
	}
}

void	stock_pos_spr(t_data *d)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	if (d->multiplayer != 1)
		ft_error("MULTIPLAYER", "");
	d->spr = malloc(sizeof(t_sprite) * d->nbr_spr);
	while (i < d->parse.map.nbr_rows)
	{
		j = 0;
		while (j < d->parse.map.nbr_cols)
		{
			if (d->parse.map.map[i][j] == '2')
			{
				d->spr[count].spr_x = (TILE_SIZE * j) + TILE_SIZE / 2;
				d->spr[count].spr_y = (TILE_SIZE * i) + TILE_SIZE / 2;
				count++;
			}
			j++;
		}
		i++;
	}
}

void	find_sprit(t_data *d)
{
	int count;

	count = 0;
	while (count < d->nbr_spr)
	{
		d->spr[count].dist_x =
		distbetweenpoints(d->spr[count].spr_x,
		d->spr[count].spr_y, d->p.pl_x,
		d->p.pl_y);
		count++;
	}
	ft_sort_sprite(d, 0, 0, count);
	draw_sprite(d, count);
}
