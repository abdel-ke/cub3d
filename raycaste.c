/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:25:38 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 11:37:46 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray(t_data *d)
{
	d->r_cst.rayangle = normalizeAngle(d->r_cst.rayangle);
	d->r_cst.wallhit_x = 0;
	d->r_cst.wallhit_y = 0;
	d->r_cst.dist = 0;
	d->r_cst.was_hitvert = 0;
	d->r_cst.is_ray_down = d->r_cst.rayangle > 0 && d->r_cst.rayangle < M_PI;
	d->r_cst.is_ray_up = !d->r_cst.is_ray_down;
	d->r_cst.is_ray_right = d->r_cst.rayangle < M_PI / 2 ||
	d->r_cst.rayangle > 3 * M_PI / 2;
	d->r_cst.is_ray_lft = !d->r_cst.is_ray_right;
	d->r_cst.founhorzwallhit = 0;
	d->r_cst.nexthorztouchx = 0;
	d->r_cst.nexthorztouchy = 0;
	d->r_cst.horzwallhit_x = 0;
	d->r_cst.horzwallhit_y = 0;
	d->r_cst.founvertwallhit = 0;
	d->r_cst.nextverttouchx = 0;
	d->r_cst.nextverttouchy = 0;
	d->r_cst.vertwallhit_x = 0;
	d->r_cst.vertwallhit_y = 0;
}

double	normalizeAngle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

double	distBetweenPoints(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
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
	// incremet xtep and ystep until we find a wall
	while (d->r_cst.nexthorztouchx >= 0 &&
	d->r_cst.nexthorztouchx <= TILE_SIZE * MAP_NUM_COLS &&
	d->r_cst.nexthorztouchy >= 0 && d->r_cst.nexthorztouchy <=
	TILE_SIZE * MAP_NUM_ROWS)
	{
		if (isWallAt(d->r_cst.nexthorztouchx,
		d->r_cst.nexthorztouchy - d->r_cst.is_ray_up) == 1)
		{
			d->r_cst.founhorzwallhit = 1;
			d->r_cst.horzwallhit_x = d->r_cst.nexthorztouchx;
			d->r_cst.horzwallhit_y = d->r_cst.nexthorztouchy;
			break;
		}
		else
		{
			d->r_cst.nexthorztouchx += d->r_cst.xstep;
			d->r_cst.nexthorztouchy += d->r_cst.ystep;
		}
	}
}

void	find_vertical_wall(t_data *d)
{
	d->r_cst.xintercept = floor(d->p.pl_x / TILE_SIZE) * TILE_SIZE;
	d->r_cst.xintercept += d->r_cst.is_ray_right ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	d->r_cst.yintercept = d->p.pl_y + ((d->r_cst.xintercept - d->p.pl_x) * tan(d->r_cst.rayangle));

	// Calculate the increment xstep and ystep
	d->r_cst.xstep = TILE_SIZE;
	d->r_cst.xstep *= d->r_cst.is_ray_lft ? -1 : 1;

	d->r_cst.ystep = TILE_SIZE * tan(d->r_cst.rayangle);
	d->r_cst.ystep *= (d->r_cst.is_ray_up && d->r_cst.ystep > 0) ? -1 : 1;
	d->r_cst.ystep *= (d->r_cst.is_ray_down && d->r_cst.ystep < 0) ? -1 : 1;

	d->r_cst.nextverttouchx = d->r_cst.xintercept;
	d->r_cst.nextverttouchy = d->r_cst.yintercept;
	/*if (d->raycast.is_ray_lft)
		d->raycast.nextverttouchx--;*/

	// incremet xtep and ystep until we find a wall
	while (d->r_cst.nextverttouchx >= 0 && d->r_cst.nextverttouchx <= TILE_SIZE * MAP_NUM_COLS &&
		   d->r_cst.nextverttouchy >= 0 && d->r_cst.nextverttouchy <= TILE_SIZE * MAP_NUM_ROWS)
	{
		if (isWallAt(d->r_cst.nextverttouchx - d->r_cst.is_ray_lft, d->r_cst.nextverttouchy) == 1)
		{
			d->r_cst.founvertwallhit = 1;
			d->r_cst.vertwallhit_x = d->r_cst.nextverttouchx;
			d->r_cst.vertwallhit_y = d->r_cst.nextverttouchy;
			// ddaa(d, d->player.pl_x, d->player.pl_y, vertwallhit_x, vertwallhit_y);
			break;
		}
		else
		{
			d->r_cst.nextverttouchx += d->r_cst.xstep;
			d->r_cst.nextverttouchy += d->r_cst.ystep;
		}
	}
}

void	calculate(t_data *d)
{
	d->r_cst.horzhitdist = (d->r_cst.founhorzwallhit)
	? distBetweenPoints(d->p.pl_x, d->p.pl_y, d->r_cst.horzwallhit_x,
	d->r_cst.horzwallhit_y) : __INT_MAX__;
	d->r_cst.verthitdist = (d->r_cst.founvertwallhit)
	? distBetweenPoints(d->p.pl_x, d->p.pl_y, d->r_cst.vertwallhit_x,
	d->r_cst.vertwallhit_y) : __INT_MAX__;
	d->r_cst.wallhit_x = (d->r_cst.horzhitdist < d->r_cst.verthitdist) ?
	d->r_cst.horzwallhit_x : d->r_cst.vertwallhit_x;
	d->r_cst.wallhit_y = (d->r_cst.horzhitdist < d->r_cst.verthitdist) ?
	d->r_cst.horzwallhit_y : d->r_cst.vertwallhit_y;
	d->r_cst.dist = (d->r_cst.horzhitdist < d->r_cst.verthitdist) ?
	d->r_cst.horzhitdist : d->r_cst.verthitdist;
	d->r_cst.was_hitvert = (d->r_cst.verthitdist < d->r_cst.horzhitdist);
}

void	cast(t_data *d)
{
	init_ray(d);
	find_horizontall_wall(d);
	find_vertical_wall(d);
	calculate(d);
	ddaa(d, d->p.pl_x * MINI_MAP, d->p.pl_y * MINI_MAP,
	d->r_cst.wallhit_x * MINI_MAP, d->r_cst.wallhit_y * MINI_MAP);
}

void	castAllRays(t_data *d)
{
	int i;
	d->r_cst.rayangle = d->p.rot_an - (FOV_ANGLE / 2);
	i = 0;
	while (i < d->num_rays)
	{
		cast(d);
		d->r_cst.dist_ray[i] = d->r_cst.dist;
		render3DProjectedWalls(d, i);
		d->r_cst.rayangle += (FOV_ANGLE / (d->num_rays));
		i++;
	}
	find_sprit(d);
	mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr, d->load_img, 0, 0);
}

void	rect(t_data *d, int x, int y, double tile_x, double tile_y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < tile_x)
	{
		j = -1;
		while (++j < tile_y)
			d->load_data[y * d->win_w + x] = color;
		i++;
	}
}

int		is_text_up_down(t_data *d)
{
	if (!d->r_cst.is_ray_up)
		d->index = 0;
	else if (!d->r_cst.is_ray_down)
		d->index = 1;
	return ((int)d->r_cst.wallhit_x % TILE_SIZE *
	d->txt[d->index].width / TILE_SIZE);
}

int		is_text_left_right(t_data *d)
{
	if (!d->r_cst.is_ray_lft)
		d->index = 2;
	else if (!d->r_cst.is_ray_right)
		d->index = 3;
	return ((int)d->r_cst.wallhit_y % TILE_SIZE *
	d->txt[d->index].width / TILE_SIZE);
}

int		was_hitvert(t_data *d)
{
	if (!d->r_cst.was_hitvert)
		return is_text_up_down(d);
	else
		return is_text_left_right(d);
}

void	render3DProjectedWalls(t_data *d, int i)
{
	int j;

	d->r_cst.raydist = d->r_cst.dist * cos(d->r_cst.rayangle - d->p.rot_an);
	d->r_cst.distbprojectplane = (d->win_w / 2) / tan(FOV_ANGLE / 2);
	d->r_cst.wallstripheight = (TILE_SIZE / d->r_cst.raydist) *
	d->r_cst.distbprojectplane;
	d->rndr.start = d->win_h / 2 - d->r_cst.wallstripheight / 2;
	d->rndr.end = d->win_h / 2 + d->r_cst.wallstripheight / 2;
	d->rndr.xtex = was_hitvert(d);
	d->rndr.color = 0;
	j = 0;
	if (d->rndr.start < 0)
		j += -d->rndr.start;
	if (d->rndr.end > d->win_h)
	{
		d->rndr.end = d->win_h;
		d->rndr.start = 0;
	}
	while (d->rndr.start < d->rndr.end)
	{
		d->rndr.ytex = j * ((double)d->txt[d->index].height /
		(double)d->r_cst.wallstripheight);
		d->rndr.color = d->txt[d->index].data[d->rndr.ytex *
		d->txt[d->index].width + d->rndr.xtex];
		if (d->rndr.start >= 0 && d->rndr.start < d->win_h)
		{
			d->load_data[(d->win_w * d->rndr.start) + i] = d->rndr.color;
			j++;
		}
		d->rndr.start++;
	}
}
