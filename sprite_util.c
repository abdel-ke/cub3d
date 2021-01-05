/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:10:47 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/05 18:03:53 by abdel-ke         ###   ########.fr       */
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
			cube->spr[i].spr_angle = cube->spr[i + 1].spr_angle;
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
	cube->spr[sprite_indice].dist_x) * cube->r_cst.distbprojectplane;
	opp = cube->spr->height / 2;
	cube->spr->ag = atan(opp / cube->r_cst.distbprojectplane);
	vectx = (cube->spr[sprite_indice].spr_x) - cube->p.pl_x;
	vecty = (cube->spr[sprite_indice].spr_y) - cube->p.pl_y;
	angle = atan2(vecty, vectx);
	if (angle <= 0.)
		angle = (2 * M_PI) + angle;
	diffangle = cube->p.rot_an - angle;
	diffangle = ft_diffangle(diffangle);
	diffangle = fabs(diffangle);
	if (diffangle - cube->spr->ag < ((FOV_ANGLE / 2)))
		return (1);
	else
		return (0);
}

void	found_spr_angle(t_data *cube, int i)
{
	double	spriteangle;
	double	x;
	double	y;

	x = cube->spr[i].spr_x - cube->p.pl_x;
	y = cube->spr[i].spr_y - cube->p.pl_y;
	spriteangle = atan2(y, x);
	if (spriteangle <= 0.)
		cube->spr[i].spr_angle =
			(M_PI * 2) + spriteangle;
	else
		cube->spr[i].spr_angle = spriteangle;
}

void	dist_to_spr(t_data *t)
{
	int count;

	count = 0;
	while (count < t->nbr_spr)
	{
		t->spr[count].dist_x = distbetweenpoints(t->p.pl_x,
		t->p.pl_y, t->spr[count].spr_x, t->spr[count].spr_y);
		count++;
	}
}
