/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:54:07 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/05 18:19:03 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	main_texture(t_data *d)
{
	d->txt[0].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr,
	"parcing/textures/SO.XPM", &d->txt[0].width, &d->txt[0].height);
	d->txt[0].data = (int *)mlx_get_data_addr(d->txt[0].img,
	&d->txt[0].bits_per_pixel, &d->txt[0].size_line, &d->txt[0].endian);
	d->txt[1].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr,
	"parcing/textures/NO.XPM", &d->txt[1].width, &d->txt[1].height);
	d->txt[1].data = (int *)mlx_get_data_addr(d->txt[1].img,
	&d->txt[1].bits_per_pixel, &d->txt[1].size_line, &d->txt[1].endian);
	d->txt[2].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr,
	"parcing/textures/EA.XPM", &d->txt[2].width, &d->txt[2].height);
	d->txt[2].data = (int *)mlx_get_data_addr(d->txt[2].img,
	&d->txt[2].bits_per_pixel, &d->txt[2].size_line, &d->txt[2].endian);
	d->txt[3].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr,
	"parcing/textures/WE.XPM", &d->txt[3].width, &d->txt[3].height);
	d->txt[3].data = (int *)mlx_get_data_addr(d->txt[3].img,
	&d->txt[3].bits_per_pixel, &d->txt[3].size_line, &d->txt[3].endian);
	d->spr->img_spr = mlx_xpm_file_to_image(d->mlx.mlx_ptr,
	"parcing/textures/barrel.XPM", &d->spr->width, &d->spr->height1);
	d->spr->data_spr = (int *)mlx_get_data_addr(d->spr->img_spr,
	&d->spr->bits_per_pixel, &d->spr->size_line, &d->spr->endian);
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

double	normalizeangle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
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
