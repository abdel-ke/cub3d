/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:58:15 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 19:53:12 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	dist_to_spr(t_data *t)
{
	int count;

	count = 0;
	while (count < t->nbr_spr)
	{
		t->spr[count].dist_x = distBetweenPoints(t->p.pl_x,
		t->p.pl_y, t->spr[count].spr_x, t->spr[count].spr_y);
		count++;
	}
}
