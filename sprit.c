/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:38:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/10 18:10:38 by abdel-ke         ###   ########.fr       */
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

void	drowsprite(t_data *cube, int i)
{
	int x;
	int y;

	y = 0;
	x = 0;
	cube->spr->height = (TILE_SIZE /
	cube->spr[i].dist_x) * cube->r_cst.distbprojectplane;
	cube->spr->end = (cube->parse.p_h / 2) + (cube->spr->height / 2);
	cube->spr->x_star_wind = (tan((FOV_ANGLE) / 2)
	* cube->r_cst.distbprojectplane) + (tan(cube->spr[i].spr_angle
	- cube->p.rot_an) * cube->r_cst.distbprojectplane)
	- (cube->spr->height / 2);
	while (x < cube->spr->height)
	{
		if (cube->spr->x_star_wind >= 0 &&
		cube->spr->x_star_wind < cube->parse.p_w)
			drow_strips(cube, cube->spr->x_star_wind, i, x);
		x++;
		cube->spr->x_star_wind++;
	}
}

void	draw_sprite(t_data *cube, int count)
{
	int i;

	i = 0;
	cube->p.rot_an = normalizeangle(cube->p.rot_an);
	while (i < count)
	{
		found_spr_angle(cube, i);
		if (sprite_visible(cube, i) == 1)
			drowsprite(cube, i);
		i++;
	}
}

void	stock_pos_spr(t_data *t)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	t->spr = malloc(sizeof(t_sprite) * t->nbr_spr);
	while (i < t->parse.map.nbr_rows)
	{
		j = 0;
		while (j < t->parse.map.nbr_cols)
		{
			if (t->parse.map.map[i][j] == '2')
			{
				t->spr[count].spr_x = (TILE_SIZE * j) + TILE_SIZE / 2;
				t->spr[count].spr_y = (TILE_SIZE * i) + TILE_SIZE / 2;
				count++;
			}
			j++;
		}
		i++;
	}
}

void	find_sprit(t_data *cube)
{
	int count;

	count = 0;
	while (count < cube->nbr_spr)
	{
		cube->spr[count].dist_x =
		distbetweenpoints(cube->spr[count].spr_x,
		cube->spr[count].spr_y, cube->p.pl_x,
		cube->p.pl_y);
		count++;
	}
	ft_sort_sprite(cube, 0, 0, count);
	draw_sprite(cube, count);
}
