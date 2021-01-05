/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:05:38 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/05 18:35:55 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	initial_player(t_data *d)
{
	d->p.rad = TILE_SIZE * 10 / 100 * MINI_MAP;
	d->win_w = 1080;
	d->win_h = 920;
	d->num_rays = d->win_w / WALL_STRIP_WIDTH;
	d->p.rot_an = M_PI;
	d->p.mv_spd = 5.0;
	d->p.rot_spd = 2 * (M_PI / 180);
	d->nbr_spr = 0;
	d->r_cst.dist_ray = (int *)malloc(sizeof(d->r_cst.dist_ray) * d->win_w);
	find_player(d);
}

void	init_ray(t_data *d)
{
	d->r_cst.rayangle = normalizeangle(d->r_cst.rayangle);
	d->r_cst.wallhit_x = 0;
	d->r_cst.wallhit_y = 0;
	d->r_cst.dist = 0;
	d->r_cst.was_hitvert = 0;
	d->r_cst.is_ray_down = d->r_cst.rayangle > 0 && d->r_cst.rayangle < M_PI;
	d->r_cst.is_ray_up = !d->r_cst.is_ray_down;
	d->r_cst.is_ray_right = d->r_cst.rayangle < M_PI / 2 ||
	d->r_cst.rayangle > 3 * M_PI / 2;
	d->r_cst.is_ray_lft = !d->r_cst.is_ray_right;
	d->r_cst.founhorzwallhit = 0;
	d->r_cst.nexthorztouchx = 0;
	d->r_cst.nexthorztouchy = 0;
	d->r_cst.horzwallhit_x = 0;
	d->r_cst.horzwallhit_y = 0;
	d->r_cst.founvertwallhit = 0;
	d->r_cst.nextverttouchx = 0;
	d->r_cst.nextverttouchy = 0;
	d->r_cst.vertwallhit_x = 0;
	d->r_cst.vertwallhit_y = 0;
}

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
