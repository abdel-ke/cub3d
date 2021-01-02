/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:19 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/16 17:41:34 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_sort_sprite(t_data *cube, double spx, double spy, int count)
{
	double	dist;
	int		i;

	i = 0;
	while (i < count - 1)
	{
		spx = cube->spr[i].spr_x;
		spy = cube->spr[i].spr_y;
		dist = cube->spr[i].dist_x;
		if (dist < cube->spr[i + 1].dist_x)
		{
			cube->spr[i].spr_x = cube->spr[i + 1].spr_x;
			cube->spr[i].spr_y = cube->spr[i + 1].spr_y;
			cube->spr[i].dist_x = cube->spr[i + 1].dist_x;
			cube->spr[i].sprite_angle = cube->spr[i + 1].sprite_angle;
			cube->spr[i + 1].spr_x = spx;
			cube->spr[i + 1].spr_y = spy;
			cube->spr[i + 1].dist_x = dist;
			i = -1;
		}
		i++;
	}
}

double	ft_diffangle(double diffangle)
{
	if (diffangle < -3.14159)
		diffangle += 2.0 * 3.14159;
	if (diffangle > 3.14159)
		diffangle -= 2.0 * 3.14159;
	return (diffangle);
}

int		sprite_visible(t_data *cube, int sprite_indice)
{
	double vectx;
	double vecty;
	double angle;
	double diffangle;
	double opp;

	cube->spr->height = (TILE_SIZE /
	cube->spr[sprite_indice].dist_x) * cube->raycast.distancebprojectionplane;
	opp = cube->spr->height / 2;
	cube->spr->ag = atan(opp / cube->raycast.distancebprojectionplane);
	vectx = (cube->spr[sprite_indice].spr_x) - cube->player.player_x;
	vecty = (cube->spr[sprite_indice].spr_y) - cube->player.player_y;
	angle = atan2(vecty, vectx);
	if (angle <= 0.)
		angle = (2 * M_PI) + angle;
	diffangle = cube->player.rotationAngle - angle;
	diffangle = ft_diffangle(diffangle);
	diffangle = fabs(diffangle);
	if (diffangle - cube->spr->ag < ((FOV_ANGLE / 2)))
		{//puts("yes");
			return (1);}
	else
		return (0);
}

void	found_sprite_angle(t_data *cube, int i)
{
	double	spriteangle;
	double	x;
	double	y;

	// spriteangle = 0;
	x = cube->spr[i].spr_x - cube->player.player_x;
	y = cube->spr[i].spr_y - cube->player.player_y;
	spriteangle = atan2(y, x);
	if (spriteangle <= 0.)
		cube->spr[i].sprite_angle =
			(M_PI * 2) + spriteangle;
	else
		cube->spr[i].sprite_angle = spriteangle;
	// cube->spr[i].sprite_angle =
	// 	normalizeAngle(cube->spr[i].sprite_angle);
}

void	drow_strips(t_data *t, int s_x, int i, int x)
{
	int y;
	int xtext;
	int ytext;
	int start;
	int color;

	start = -1;
	y = 0;
	// start = (cube->m.height / 2) - (cube->sprits->hight / 2);
	start = (t->win_h / 2) - (t->spr->height / 2);
	t->spr->end =  (t->win_h / 2) + (t->spr->height / 2);
	if (start < 0)
	{
		y = -start;
		start = -1;
	}
	xtext = x * (64 / (double)t->spr->height);
	if (t->spr->end > t->win_h)
		t->spr->end = t->win_h;
	while (++start < t->spr->end)
	{
		ytext = y * (64 / (double)t->spr->height);
		color = t->spr->data_spr[ytext * 64 + xtext];
		// if (cube->ray.dist_tab[s_x] > cube->sprits[i].dist_to_player)
		if (t->raycast.dist_ray[s_x] > t->spr[i].dist_x)
			if (color != 0x00000)
				t->load_data[start * t->win_w + s_x] = color;
				// cube->data[start * cube->m.witdth + s_x] = color;
		y++;
	}
}

void	drowsprite(t_data *cube, int i)
{
	int x;
	int y;

	y = 0;
	x = 0;
	// cube->spr[i].dist_x = cube->spr[i].dist_x
	// * cos(cube->raycast.rayangle- cube->player.rotationAngle);
	cube->spr->height = (TILE_SIZE /
	cube->spr[i].dist_x) * cube->raycast.distancebprojectionplane;
	cube->spr->end = (cube->win_h / 2) + (cube->spr->height / 2);
	cube->spr->x_star_wind = (tan((FOV_ANGLE ) / 2)
	* cube->raycast.distancebprojectionplane) + (tan(cube->spr[i].sprite_angle
	- cube->player.rotationAngle) * cube->raycast.distancebprojectionplane)
	- (cube->spr->height / 2);
	//printf("%f\n",cube->spr->x_star_wind);
	while (x < cube->spr->height)
	{
		if (cube->spr->x_star_wind >= 0 &&
		cube->spr->x_star_wind < cube->win_w)
			drow_strips(cube, cube->spr->x_star_wind, i, x);
		x++;
		cube->spr->x_star_wind++;
	}
}

void	draw_sprite(t_data *cube, int count)
{
	int i;

	i = 0;

	cube->player.rotationAngle = normalizeAngle(cube->player.rotationAngle);
	while (i < count)
	{
		found_sprite_angle(cube, i);
		if (sprite_visible(cube, i) == 1)
			{
				drowsprite(cube, i);
			}
		i++;
	}
}

void stock_pos_spr(t_data *t)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	t->spr = malloc(sizeof(t_sprite) * t->nbr_spr);
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == '2')
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
		// sqrt(pow(cube->spr[count].spr_x - cube->spr[count].spr_y, 2) +
		// pow(cube->player.player_x - cube->player.player_y, 2));
		distanceBetweenPoints(cube->spr[count].spr_x,
		cube->spr[count].spr_y, cube->player.player_x,
		cube->player.player_y);
		count++;
	}
	ft_sort_sprite(cube, 0, 0, count);
	draw_sprite(cube, count);
}
