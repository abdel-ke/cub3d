/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:49:07 by abdel-ke          #+#    #+#             */
/*   Updated: 2020/11/19 14:39:04 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void main_texture(t_data *t)
{
	t->txt.img = mlx_xpm_file_to_image(t->mlx.mlx_ptr, "image/wall1.xpm", &t->txt.width,
									   &t->txt.height);
	t->txt.data = (int *)mlx_get_data_addr(t->txt.img, &t->txt.bits_per_pixel,
										   &t->txt.size_line, &t->txt.endian);
	int i = -1, x = 0;
	while (x++ != 355)
	{
		i = 0;
		while (i++ < 355)
			t->txt.load_data[i * 355 + x] = t->txt.data[i * 355 + x];
	}
}