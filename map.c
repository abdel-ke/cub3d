/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:10:09 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/10 18:32:14 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		draw(t_data *d)
{
	mlx_destroy_image(d->mlx.mlx_ptr, d->load_img);
	d->load_img = mlx_new_image(d->mlx.mlx_ptr, d->parse.p_w, d->parse.p_h);
	update_player(d);
	sky_floor_color(d);
	castallrays(d);
	if (d->parse.handle == 0)
		mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr, d->load_img,
		0, 0);
	else
		ft_save(d);
	return (0);
}
