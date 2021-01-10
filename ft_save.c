/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:18:28 by abettach          #+#    #+#             */
/*   Updated: 2021/01/10 18:21:35 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void		bmp_image(t_data *d, int fd)
{
	int y;
	int x;

	x = d->parse.p_h - 1;
	while (x >= 0)
	{
		y = 0;
		while (y < d->parse.p_w)
		{
			write(fd, &d->load_data[x * d->parse.p_w + y], 4);
			y++;
		}
		x--;
	}
}

static void		info_header(t_data *d, int fd)
{
	int info_header_size;
	int plane;
	int i;

	info_header_size = 40;
	plane = 1;
	write(fd, &info_header_size, 4);
	write(fd, &d->parse.p_w, 4);
	write(fd, &d->parse.p_h, 4);
	write(fd, &plane, 2);
	write(fd, &d->mlx.bits_per_pixel, 2);
	i = 0;
	while (i++ < 32)
		write(fd, "\0", 1);
}

static void		creat_bmp(t_data *d)
{
	int size;
	int fd;
	int dataoffset;

	dataoffset = 54;
	fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0640);
	dataoffset = 54;
	size = dataoffset + (4 * (d->parse.p_w * d->parse.p_h));
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &dataoffset, 4);
	info_header(d, fd);
	bmp_image(d, fd);
	close(fd);
}

void			ft_save(t_data *d)
{
	creat_bmp(d);
	exit(0);
}

int				ft_check_save(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'e' && str[i - 2] == 'v' && str[i - 3] == 'a' &&
		str[i - 4] == 's' && str[i - 5] == '-' && str[i - 6] == '-'
		&& ft_strlen(str) < 7)
		return (1);
	else
		return (0);
}
