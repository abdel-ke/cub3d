/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 09:58:25 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/05 18:19:18 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		iswallat(int x, int y)
{
	int mapx;
	int mapy;

	mapx = x / TILE_SIZE;
	mapy = y / TILE_SIZE;
	if (map[mapy][mapx] == '1')
		return (1);
	if (map[mapy][mapx] == '2')
		return (2);
	return (0);
}

void	put_player(t_data *d, int i, int j, double rotation)
{
	d->p.rot_an = rotation;
	d->p.pl_y = i * TILE_SIZE + TILE_SIZE / 2;
	d->p.pl_x = j * TILE_SIZE + TILE_SIZE / 2;
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

void	update_player(t_data *d)
{
	double mv_stp;
	double mv_stp1;
	double new_p_x;
	double new_p_y;

	d->p.rot_an += d->p.turn_dir * d->p.rot_spd;
	if (d->p.walk_dir != 0)
	{
		mv_stp = d->p.walk_dir * d->p.mv_spd;
		new_p_x = d->p.pl_x + cos(d->p.rot_an) * mv_stp;
		new_p_y = d->p.pl_y + sin(d->p.rot_an) * mv_stp;
	}
	if (d->p.st_side != 0)
	{
		mv_stp1 = d->p.st_side * d->p.mv_spd;
		new_p_x = d->p.pl_x + cos(d->p.rot_an - (90 * M_PI / 180)) * mv_stp1;
		new_p_y = d->p.pl_y + sin(d->p.rot_an - (90 * M_PI / 180)) * mv_stp1;
	}
	if (!iswallat(d->p.pl_x, new_p_y))
		d->p.pl_y = new_p_y;
	if (!iswallat(new_p_x, d->p.pl_y))
		d->p.pl_x = new_p_x;
}
