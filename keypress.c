/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:15:48 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 19:41:12 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		keypressed(int key, t_data *d)
{
	d->p.walk_dir = 0;
	d->p.turn_dir = 0;
	d->p.st_side = 0;
	if (key == UP_KEY)
		d->p.walk_dir = 1;
	if (key == DOWN_KEY)
		d->p.walk_dir = -1;
	if (key == RIGHT_KEY)
		d->p.turn_dir = 1;
	if (key == LEFT_KEY)
		d->p.turn_dir = -1;
	if (key == A_KEY)
		d->p.st_side = +1;
	if (key == D_KEY)
		d->p.st_side = -1;
	if (key == QUIT_KEY)
		exit(0);
	return (0);
}

int		keyrealease(int key, t_data *d)
{
	if (key == UP_KEY)
		d->p.walk_dir = 0;
	if (key == DOWN_KEY)
		d->p.walk_dir = 0;
	if (key == RIGHT_KEY)
		d->p.turn_dir = 0;
	if (key == LEFT_KEY)
		d->p.turn_dir = 0;
	if (key == A_KEY)
		d->p.st_side = 0;
	if (key == D_KEY)
		d->p.st_side = 0;
	return (0);
}
