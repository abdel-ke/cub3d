/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:15:48 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/07 17:08:45 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		keyrealease(int key, t_data *d)
{
	if (key == W_KEY || key == S_KEY)
		d->p.walk_dir = 0;
	if (key == D_KEY || key == A_KEY)
		d->p.st_side = 0;
	if (key == LEFT_KEY || key == RIGHT_KEY)
		d->p.turn_dir = 0;
	return (0);
}
