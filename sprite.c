/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:58:15 by abdel-ke          #+#    #+#             */
/*   Updated: 2020/12/13 16:59:02 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	dist_to_spr(t_data *t)
{
	int count = 0;
	puts("ok");
	while (count < t->nbr_spr)
	{
		t->spr[count].dist_x = distanceBetweenPoints(t->player.player_x,
		t->player.player_y, t->spr[count].spr_x, t->spr[count].spr_y);
		// t->spr[count].dist_y = distanceBetweenPoints(t->player.player_x,
		// t->player.player_y, t->spr[count].spr_x, t->spr[count].spr_y);
		count++;
	}
}
/*
void find_sprite(t_data *t, int i, int j)
{
	t->spr[t->nbr_spr].spr_x = TILE_SIZE * i;
	t->spr[t->nbr_spr].spr_y = TILE_SIZE * j;
	t->nbr_spr++;
}
*/
