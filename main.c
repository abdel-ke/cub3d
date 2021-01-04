/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:05:38 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/04 19:41:00 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		close_win(void)
{
	exit(0);
	return (0);
}

int		main(void)
{
	t_data t;

	initial_player(&t);
	t.mlx.mlx_ptr = mlx_init();
	t.mlx.win_ptr = mlx_new_window(t.mlx.mlx_ptr, t.win_w, t.win_h, "one");
	t.load_img = mlx_new_image(t.mlx.mlx_ptr, t.win_w, t.win_h);
	t.load_data = (int *)mlx_get_data_addr(t.load_img, &t.txt[0].bits_per_pixel,
	&t.txt[0].size_line, &t.txt[0].endian);
	main_texture(&t);
	draw(&t);
	mlx_hook(t.mlx.win_ptr, 2, (1L << 0), keypressed, &t);
	mlx_hook(t.mlx.win_ptr, 3, (1L >> 0), keyrealease, &t);
	mlx_hook(t.mlx.win_ptr, 17, 1L << 5, &close_win, &t);
	mlx_loop_hook(t.mlx.mlx_ptr, draw, &t);
	mlx_loop(t.mlx.mlx_ptr);
	return (0);
}
