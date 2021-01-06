/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:25:38 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/06 15:49:02 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	find_horz_wall(t_data *d)
{
	while (d->r_cst.nexthorztouchx >= 0 &&
	d->r_cst.nexthorztouchx <= TILE_SIZE * MAP_NUM_COLS &&
	d->r_cst.nexthorztouchy >= 0 && d->r_cst.nexthorztouchy <=
	TILE_SIZE * d->parse.map.nbr_rows)
	{
		if (iswallat(d, d->r_cst.nexthorztouchx,
		d->r_cst.nexthorztouchy - d->r_cst.is_ray_up) == 1)
		{
			d->r_cst.founhorzwallhit = 1;
			d->r_cst.horzwallhit_x = d->r_cst.nexthorztouchx;
			d->r_cst.horzwallhit_y = d->r_cst.nexthorztouchy;
			break ;
		}
		else
		{
			d->r_cst.nexthorztouchx += d->r_cst.xstep;
			d->r_cst.nexthorztouchy += d->r_cst.ystep;
		}
	}
}

void	find_vert_wall(t_data *d)
{
	while (d->r_cst.nextverttouchx >= 0 &&
	d->r_cst.nextverttouchx <= TILE_SIZE * MAP_NUM_COLS &&
	d->r_cst.nextverttouchy >= 0 && d->r_cst.nextverttouchy <=
	TILE_SIZE * d->parse.map.nbr_rows)
	{
		if (iswallat(d, d->r_cst.nextverttouchx - d->r_cst.is_ray_lft,
		d->r_cst.nextverttouchy) == 1)
		{
			d->r_cst.founvertwallhit = 1;
			d->r_cst.vertwallhit_x = d->r_cst.nextverttouchx;
			d->r_cst.vertwallhit_y = d->r_cst.nextverttouchy;
			break ;
		}
		else
		{
			d->r_cst.nextverttouchx += d->r_cst.xstep;
			d->r_cst.nextverttouchy += d->r_cst.ystep;
		}
	}
}

void	find_horizontall_wall(t_data *d)
{
	d->r_cst.yintercept = floor(d->p.pl_y / TILE_SIZE) * TILE_SIZE;
	d->r_cst.yintercept += d->r_cst.is_ray_down ? TILE_SIZE : 0;
	d->r_cst.xintercept = d->p.pl_x + ((d->r_cst.yintercept - d->p.pl_y) /
	tan(d->r_cst.rayangle));
	d->r_cst.ystep = TILE_SIZE;
	d->r_cst.ystep *= d->r_cst.is_ray_up ? -1 : 1;
	d->r_cst.xstep = TILE_SIZE / tan(d->r_cst.rayangle);
	d->r_cst.xstep *= (d->r_cst.is_ray_lft && d->r_cst.xstep > 0) ? -1 : 1;
	d->r_cst.xstep *= (d->r_cst.is_ray_right && d->r_cst.xstep < 0) ? -1 : 1;
	d->r_cst.nexthorztouchx = d->r_cst.xintercept;
	d->r_cst.nexthorztouchy = d->r_cst.yintercept;
	find_horz_wall(d);
}

void	find_vertical_wall(t_data *d)
{
	d->r_cst.xintercept = floor(d->p.pl_x / TILE_SIZE) * TILE_SIZE;
	d->r_cst.xintercept += d->r_cst.is_ray_right ? TILE_SIZE : 0;
	d->r_cst.yintercept = d->p.pl_y + ((d->r_cst.xintercept - d->p.pl_x) *
	tan(d->r_cst.rayangle));
	d->r_cst.xstep = TILE_SIZE;
	d->r_cst.xstep *= d->r_cst.is_ray_lft ? -1 : 1;
	d->r_cst.ystep = TILE_SIZE * tan(d->r_cst.rayangle);
	d->r_cst.ystep *= (d->r_cst.is_ray_up && d->r_cst.ystep > 0) ? -1 : 1;
	d->r_cst.ystep *= (d->r_cst.is_ray_down && d->r_cst.ystep < 0) ? -1 : 1;
	d->r_cst.nextverttouchx = d->r_cst.xintercept;
	d->r_cst.nextverttouchy = d->r_cst.yintercept;
	find_vert_wall(d);
}

int		was_hitvert(t_data *d)
{
	if (!d->r_cst.was_hitvert)
		return (is_text_up_down(d));
	else
		return (is_text_left_right(d));
}
