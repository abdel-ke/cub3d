/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:54:07 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 19:54:36 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	main_texture(t_data *d)
{
	d->txt[0].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr, "textures/SO.XPM",
	&d->txt[0].width, &d->txt[0].height);
	d->txt[0].data = (int *)mlx_get_data_addr(d->txt[0].img,
	&d->txt[0].bits_per_pixel, &d->txt[0].size_line, &d->txt[0].endian);
	d->txt[1].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr, "textures/NO.XPM",
	&d->txt[1].width, &d->txt[1].height);
	d->txt[1].data = (int *)mlx_get_data_addr(d->txt[1].img,
	&d->txt[1].bits_per_pixel, &d->txt[1].size_line, &d->txt[1].endian);
	d->txt[2].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr, "textures/EA.XPM",
	&d->txt[2].width, &d->txt[2].height);
	d->txt[2].data = (int *)mlx_get_data_addr(d->txt[2].img,
	&d->txt[2].bits_per_pixel, &d->txt[2].size_line, &d->txt[2].endian);
	d->txt[3].img = mlx_xpm_file_to_image(d->mlx.mlx_ptr, "textures/WE.XPM",
	&d->txt[3].width, &d->txt[3].height);
	d->txt[3].data = (int *)mlx_get_data_addr(d->txt[3].img,
	&d->txt[3].bits_per_pixel, &d->txt[3].size_line, &d->txt[3].endian);
	d->spr->img_spr = mlx_xpm_file_to_image(d->mlx.mlx_ptr,
	"textures/barrel.XPM", &d->spr->width, &d->spr->height1);
	d->spr->data_spr = (int *)mlx_get_data_addr(d->spr->img_spr,
	&d->spr->bits_per_pixel, &d->spr->size_line, &d->spr->endian);
}
