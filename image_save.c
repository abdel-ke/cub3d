/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:12:18 by ymarji            #+#    #+#             */
/*   Updated: 2021/01/09 17:45:16 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	image_header(t_image *image, int file)
{
	unsigned char	str[54];

	ft_bzero(str, 54);
	ft_memcpy(str, "BM", 2);
	ft_memcpy(str + 2, &image->file_size, 4);
	ft_memcpy(str + 10, &image->offset_bits, 4);
	ft_memcpy(str + 14, &image->size_header, 4);
	ft_memcpy(str + 18, &image->width, 4);
	ft_memcpy(str + 22, &image->height, 4);
	ft_memcpy(str + 26, &image->planes, 2);
	ft_memcpy(str + 28, &image->bit_count, 2);
	ft_memcpy(str + 34, &image->image_size, 4);
	write(file, &str, 54);
}

void	fill_data(t_image *image, t_data *d)
{
	image->file_size = (d->parse.p_w * d->parse.p_h * 4) + 54;
	image->reserved1 = 0;
	image->reserved2 = 0;
	image->offset_bits = 0;
	image->size_header = 40;
	image->width = d->parse.p_w;
	image->height = d->parse.p_h;
	image->planes = 1;
	image->bit_count = 24;
	image->compression = 0;
	image->image_size = image->file_size - 54;
	image->ppm_x = 0;
	image->ppm_y = 0;
	image->clr_used = 0;
	image->clr_important = 0;
}

void	image_put(t_data *d, t_image *image, int file)
{
	int				color;
	unsigned char	*buf;
	int				row;
	int				col;

	row = image->height - 1;
	buf = malloc(image->file_size);
	while (row >= 0)
	{
		col = 0;
		while (col < (int)image->width)
		{
			color = d->txt->data[(d->parse.p_h - row) *
			image->width + col];
			buf[row * image->width * 3 + col * 3 + 0] = color;
			buf[row * image->width * 3 + col * 3 + 1] = color >> 8;
			buf[row * image->width * 3 + col * 3 + 2] = color >> 16;
			col++;
		}
		row--;
	}
	write(file, buf, image->file_size);
	free(buf);
}

void	image_create(t_data *cube)
{
	t_image	image;
	int		file;

	file = open("./save.bmp", O_RDWR | O_CREAT, 777);
	fill_data(&image, cube);
	image_header(&image, file);
	image_put(cube, &image, file);
}
