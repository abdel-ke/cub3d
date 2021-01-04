/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:34:36 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 19:35:24 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	find_player(t_data *d)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == 'N')
				put_player(d, i, j, 3 * M_PI / 2);
			else if (map[i][j] == 'W')
				put_player(d, i, j, M_PI);
			else if (map[i][j] == 'E')
				put_player(d, i, j, 0);
			else if (map[i][j] == 'S')
				put_player(d, i, j, M_PI / 2);
			else if (map[i][j] == '2')
				d->nbr_spr++;
			j++;
		}
		i++;
	}
	stock_pos_spr(d);
}