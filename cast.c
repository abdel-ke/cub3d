/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:39:34 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/11 17:51:57 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	cast(t_data *d)
{
	init_ray(d);
	find_horizontall_wall(d);
	find_vertical_wall(d);
	calculate(d);
}

void	castallrays(t_data *d)
{
	int i;

	i = 0;
	d->r_cst.rayangle = d->p.rot_an - (FOV_ANGLE / 2);
	d->r_cst.dist_ray = (int *)malloc(sizeof(d->r_cst.dist_ray) * d->parse.p_w);
	while (i < d->parse.p_w)
	{
		cast(d);
		d->r_cst.dist_ray[i] = d->r_cst.dist;
		render3dprojectedwalls(d, i, 0);
		d->r_cst.rayangle += (FOV_ANGLE / (d->parse.p_w));
		i++;
	}
	find_sprit(d);
	free(d->r_cst.dist_ray);
}

void	calculate(t_data *d)
{
	d->r_cst.horzhitdist = (d->r_cst.founhorzwallhit)
	? distbetweenpoints(d->p.pl_x, d->p.pl_y, d->r_cst.horzwallhit_x,
	d->r_cst.horzwallhit_y) : __INT_MAX__;
	d->r_cst.verthitdist = (d->r_cst.founvertwallhit)
	? distbetweenpoints(d->p.pl_x, d->p.pl_y, d->r_cst.vertwallhit_x,
	d->r_cst.vertwallhit_y) : __INT_MAX__;
	d->r_cst.wallhit_x = (d->r_cst.horzhitdist < d->r_cst.verthitdist) ?
	d->r_cst.horzwallhit_x : d->r_cst.vertwallhit_x;
	d->r_cst.wallhit_y = (d->r_cst.horzhitdist < d->r_cst.verthitdist) ?
	d->r_cst.horzwallhit_y : d->r_cst.vertwallhit_y;
	d->r_cst.dist = (d->r_cst.horzhitdist < d->r_cst.verthitdist) ?
	d->r_cst.horzhitdist : d->r_cst.verthitdist;
	d->r_cst.was_hitvert = (d->r_cst.verthitdist < d->r_cst.horzhitdist);
}

void	draw_projected_wall(t_data *d, int i, int j)
{
	while (d->rndr.start < d->rndr.end)
	{
		d->rndr.ytex = j * ((double)d->txt[d->index].height /
		(double)d->r_cst.wallstripheight);
		d->rndr.color = d->txt[d->index].data[d->rndr.ytex *
		d->txt[d->index].width + d->rndr.xtex];
		if (d->rndr.start >= 0 && d->rndr.start < d->parse.p_h)
		{
			d->load_data[(d->parse.p_w * d->rndr.start) + i] = d->rndr.color;
			j++;
		}
		d->rndr.start++;
	}
}

void	render3dprojectedwalls(t_data *d, int i, int j)
{
	d->r_cst.raydist = d->r_cst.dist * cos(d->r_cst.rayangle - d->p.rot_an);
	d->r_cst.distbprojectplane = (d->parse.p_w / 2) / tan(FOV_ANGLE / 2);
	d->r_cst.wallstripheight = (TILE_SIZE / d->r_cst.raydist) *
	d->r_cst.distbprojectplane;
	d->rndr.start = d->parse.p_h / 2 - d->r_cst.wallstripheight / 2;
	d->rndr.end = d->parse.p_h / 2 + d->r_cst.wallstripheight / 2;
	d->rndr.xtex = was_hitvert(d);
	d->rndr.color = 0;
	if (d->rndr.start < 0)
		j += -d->rndr.start;
	if (d->rndr.end > d->parse.p_h)
	{
		d->rndr.end = d->parse.p_h;
		d->rndr.start = 0;
	}
	draw_projected_wall(d, i, j);
}
