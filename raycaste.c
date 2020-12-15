/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:25:38 by abdel-ke          #+#    #+#             */
/*   Updated: 2020/12/15 18:35:22 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray(t_data *t)
{
	t->raycast.rayangle = normalizeAngle(t->raycast.rayangle);

	t->raycast.wallHitX = 0;
	t->raycast.wallHitY = 0;

	t->raycast.distance = 0;
	t->raycast.washitvertical = 0;

	t->raycast.israyfacingdown = t->raycast.rayangle > 0 && t->raycast.rayangle < M_PI;
	t->raycast.israyfacingup = !t->raycast.israyfacingdown;

	t->raycast.israyfacingright = t->raycast.rayangle < M_PI / 2 || t->raycast.rayangle > 3 * M_PI / 2;
	t->raycast.israyfacingleft = !t->raycast.israyfacingright;

	t->raycast.founhorzwallhit = 0;
	t->raycast.nexthorztouchx = 0;
	t->raycast.nexthorztouchy = 0;

	t->raycast.horzwallhitx = 0;
	t->raycast.horzwallhity = 0;

	t->raycast.founvertwallhit = 0;

	t->raycast.nextverttouchx = 0;
	t->raycast.nextverttouchy = 0;

	t->raycast.vertwallhitx = 0;
	t->raycast.vertwallhity = 0;
}

double	normalizeAngle(double angle)
{
	// angle = (int)angle % (2 * (int)M_PI);
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	/* if (angle == 2 * M_PI)// || angle < 0)
		angle = 0; */
	return (angle);
}

double	distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	// return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	find_horizontall_wall(t_data *t)
{
	// finding the intersection with the grid cells
	// Find the y-coordinate of the closest horizontal grid intersenction
	t->raycast.yintercept = floor(t->player.player_y / TILE_SIZE) * TILE_SIZE;
	t->raycast.yintercept += t->raycast.israyfacingdown ? TILE_SIZE : 0;
	// Find the x-coordinate of the closest horizontal grid intersection
	t->raycast.xintercept = t->player.player_x + ((t->raycast.yintercept - t->player.player_y) / tan(t->raycast.rayangle));
	// Calculate the increment xstep and ystep
	t->raycast.ystep = TILE_SIZE;
	t->raycast.ystep *= t->raycast.israyfacingup ? -1 : 1;
	t->raycast.xstep = TILE_SIZE / tan(t->raycast.rayangle);
	t->raycast.xstep *= (t->raycast.israyfacingleft && t->raycast.xstep > 0) ? -1 : 1;
	t->raycast.xstep *= (t->raycast.israyfacingright && t->raycast.xstep < 0) ? -1 : 1;
	t->raycast.nexthorztouchx = t->raycast.xintercept;
	t->raycast.nexthorztouchy = t->raycast.yintercept;
	/*if (t->raycast.israyfacingup)
		t->raycast.nexthorztouchy--;*/
	// incremet xtep and ystep until we find a wall
	while (t->raycast.nexthorztouchx >= 0 && t->raycast.nexthorztouchx <= WINDOW_WIDTH && t->raycast.nexthorztouchy >= 0 && t->raycast.nexthorztouchy <= WINDOW_HEIGHT)
	{
		if (isWallAt(t->raycast.nexthorztouchx, t->raycast.nexthorztouchy - t->raycast.israyfacingup) == 1)
		{
			t->raycast.founhorzwallhit = 1;
			t->raycast.horzwallhitx = t->raycast.nexthorztouchx;
			t->raycast.horzwallhity = t->raycast.nexthorztouchy;
			break;
		}
		else
		{
			t->raycast.nexthorztouchx += t->raycast.xstep;
			t->raycast.nexthorztouchy += t->raycast.ystep;
		}
	}
}

void	find_vertical_wall(t_data *t)
{
	t->raycast.xintercept = floor(t->player.player_x / TILE_SIZE) * TILE_SIZE;
	t->raycast.xintercept += t->raycast.israyfacingright ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	t->raycast.yintercept = t->player.player_y + ((t->raycast.xintercept - t->player.player_x) * tan(t->raycast.rayangle));

	// Calculate the increment xstep and ystep
	t->raycast.xstep = TILE_SIZE;
	t->raycast.xstep *= t->raycast.israyfacingleft ? -1 : 1;

	t->raycast.ystep = TILE_SIZE * tan(t->raycast.rayangle);
	t->raycast.ystep *= (t->raycast.israyfacingup && t->raycast.ystep > 0) ? -1 : 1;
	t->raycast.ystep *= (t->raycast.israyfacingdown && t->raycast.ystep < 0) ? -1 : 1;

	t->raycast.nextverttouchx = t->raycast.xintercept;
	t->raycast.nextverttouchy = t->raycast.yintercept;
	/*if (t->raycast.israyfacingleft)
		t->raycast.nextverttouchx--;*/

	// incremet xtep and ystep until we find a wall
	while (t->raycast.nextverttouchx >= 0 && t->raycast.nextverttouchx <= WINDOW_WIDTH &&
		   t->raycast.nextverttouchy >= 0 && t->raycast.nextverttouchy <= WINDOW_HEIGHT)
	{
		if (isWallAt(t->raycast.nextverttouchx - t->raycast.israyfacingleft, t->raycast.nextverttouchy) == 1)
		{
			t->raycast.founvertwallhit = 1;
			t->raycast.vertwallhitx = t->raycast.nextverttouchx;
			t->raycast.vertwallhity = t->raycast.nextverttouchy;
			// ddaa(t, t->player.player_x, t->player.player_y, vertwallhitx, vertwallhity);
			break;
		}
		else
		{
			t->raycast.nextverttouchx += t->raycast.xstep;
			t->raycast.nextverttouchy += t->raycast.ystep;
		}
	}
}

void	calculate(t_data *t)
{
	// Calculate both horizontal and vertical distances and choose the smallest value
	t->raycast.horzhitdistance = (t->raycast.founhorzwallhit)
									 ? distanceBetweenPoints(t->player.player_x, t->player.player_y,
															 t->raycast.horzwallhitx, t->raycast.horzwallhity)
									 : __INT_MAX__;
	t->raycast.verthitdistance = (t->raycast.founvertwallhit)
									 ? distanceBetweenPoints(t->player.player_x, t->player.player_y,
															 t->raycast.vertwallhitx, t->raycast.vertwallhity)
									 : __INT_MAX__;

	// only store the smallest of the distances
	t->raycast.wallHitX = (t->raycast.horzhitdistance < t->raycast.verthitdistance) ? t->raycast.horzwallhitx : t->raycast.vertwallhitx;
	t->raycast.wallHitY = (t->raycast.horzhitdistance < t->raycast.verthitdistance) ? t->raycast.horzwallhity : t->raycast.vertwallhity;
	t->raycast.distance = (t->raycast.horzhitdistance < t->raycast.verthitdistance) ? t->raycast.horzhitdistance : t->raycast.verthitdistance;
	t->raycast.washitvertical = (t->raycast.verthitdistance < t->raycast.horzhitdistance);
}

void	cast(t_data *t)
{
	init_ray(t);
	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE //
	///////////////////////////////////////////
	find_horizontall_wall(t);
	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE   //
	///////////////////////////////////////////
	find_vertical_wall(t);
	calculate(t);
	ddaa(t, t->player.player_x * MINI_MAP,
		 t->player.player_y * MINI_MAP,
		 t->raycast.wallHitX * MINI_MAP,
		 t->raycast.wallHitY * MINI_MAP);
}

void	castAllRays(t_data *t)
{
	// int columnid = 0;
	// start first ray subtracting half of the FOV
	t->raycast.rayangle = t->player.rotationAngle - (FOV_ANGLE / 2);
	// printf("%.2f\n", t->raycast.rayangle);
	int i = 0;
	while (i < NUM_RAYS)
	{
		cast(t);
		t->raycast.dist_ray[i] = t->raycast.distance;
		// printf("%d\t%d\n", t->raycast.distance, t->raycast.dist_ray[i]);
		render3DProjectedWalls(t, i);
		t->raycast.rayangle += (FOV_ANGLE / (NUM_RAYS));
		// columnid++;
		i++;
	}
	find_sprit(t);
	mlx_put_image_to_window(t->mlx.mlx_ptr, t->mlx.win_ptr, t->load_img, 0, 0);
}

void	rect(t_data *t, int x, int y, double tile_x, double tile_y, int color)
{
	int i = -1;
	int j;

	while (++i < tile_x)
	{
		j = -1;
		while (++j < tile_y)
			t->load_data[y * WINDOW_WIDTH + x] = color;
		// mlx_pixel_put(t->mlx.mlx_ptr, t->mlx.win_ptr, x + i, y + j, color);
	}
}

int		is_text_up_down(t_data *t)
{
	if (!t->raycast.israyfacingup)
		t->index = 0;
	else if (!t->raycast.israyfacingdown)
		t->index = 1;
	return ((int)t->raycast.wallHitX % TILE_SIZE * t->txt[t->index].width / TILE_SIZE);
}

int		is_text_left_right(t_data *t)
{
	if (!t->raycast.israyfacingleft)
		t->index = 2;
	else if (!t->raycast.israyfacingright)
		t->index = 3;
	return ((int)t->raycast.wallHitY % TILE_SIZE * t->txt[t->index].width / TILE_SIZE);
}

int		washitvertical(t_data *t)
{
	if (!t->raycast.washitvertical)
		return is_text_up_down(t);
	else
		return is_text_left_right(t);
}

void	render3DProjectedWalls(t_data *t, int i)
{
	// loop every ray in the array of rays
	int start;
	int end;

	t->raycast.raydistance = t->raycast.distance *
							 cos(t->raycast.rayangle - t->player.rotationAngle);

	// calculate the distance to the projection plane
	t->raycast.distancebprojectionplane = (WINDOW_WIDTH / 2) /
										  tan(FOV_ANGLE / 2);

	// projected wall height
	t->raycast.wallstripheight = (TILE_SIZE / t->raycast.raydistance) *
								 t->raycast.distancebprojectionplane;

	start = WINDOW_HEIGHT / 2 - t->raycast.wallstripheight / 2;
	end = WINDOW_HEIGHT / 2 + t->raycast.wallstripheight / 2;

	int xtex = washitvertical(t);

	// dist_to_spr(t);

	// int xtex = (int)t->raycast.wallHitY % TILE_SIZE * t->txt[t->index].width / TILE_SIZE;
	int color = 0;
	int j = 0;
	int ytex;
	if (start < 0)
		j += -start;
	if (end > WINDOW_HEIGHT)
	{
		end = WINDOW_HEIGHT;
		start = 0;
	}
	while (start < end)
	{
		ytex = j * ((double)t->txt[t->index].height / (double)t->raycast.wallstripheight);
		color = t->txt[t->index].data[ytex * t->txt[t->index].width + xtex];
		// int color2 = t->spr[0].data_spr[ytex * t->spr[0].width + xtex];
		if (start >= 0 && start < WINDOW_HEIGHT)
		{
			t->load_data[(WINDOW_WIDTH * start) + i] = color; //t->txt[0].data[(143 + j)];
			// t->load_data[(WINDOW_WIDTH * start) + i] = color2; //t->txt[0].data[(143 + j)];
			j++;
		}
		start++;
	}
	// rect(t,
	// 	 i,
	// 	 (WINDOW_HEIGHT / 2) - (wallStripHeight / 2),
	// 	 WALL_STRIP_WIDTH,
	// 	 wallStripHeight,
	// 	 0xff00ff);
}
