/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student->42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:49:07 by abdel-ke          #+#    #+#             */
/*   Updated: 2020/12/06 18:15:52 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void main_texture(t_data *t)
{
	if (!(t->txt[0].img = mlx_xpm_file_to_image(t->mlx.mlx_ptr, "./image/SO.XPM",
	&t->txt[0].width, &t->txt[0].height)))
	t->txt[0].data = (int *)mlx_get_data_addr(t->txt[0].img,
	&t->txt[0].bits_per_pixel, &t->txt[0].size_line, &t->txt[0].endian);
	// puts("ok");
	if (!(t->txt[1].img = mlx_xpm_file_to_image(t->mlx.mlx_ptr, "image/NO.XPM",
	&t->txt[1].width, &t->txt[1].height)))
	t->txt[1].data = (int *)mlx_get_data_addr(t->txt[1].img,
	&t->txt[1].bits_per_pixel, &t->txt[1].size_line, &t->txt[1].endian);
	if (!(t->txt[2].img = mlx_xpm_file_to_image(t->mlx.mlx_ptr, "image/4.XPM",
	&t->txt[2].width, &t->txt[2].height)))
	t->txt[2].data = (int *)mlx_get_data_addr(t->txt[2].img,
	&t->txt[2].bits_per_pixel, &t->txt[2].size_line, &t->txt[2].endian);
	if (!(t->txt[3].img = mlx_xpm_file_to_image(t->mlx.mlx_ptr, "image/1.XPM",
	&t->txt[3].width, &t->txt[3].height)))
	t->txt[3].data = (int *)mlx_get_data_addr(t->txt[3].img,
	&t->txt[3].bits_per_pixel, &t->txt[3].size_line, &t->txt[3].endian);
	if (!(t->spr->img_spr = mlx_xpm_file_to_image(t->mlx.mlx_ptr, "image/barrel.XPM",
	&t->spr->width, &t->spr->height1)))
	t->spr->data_spr = (int *)mlx_get_data_addr(t->spr->img_spr,
	&t->spr->bits_per_pixel, &t->spr->size_line, &t->spr->endian);
}
