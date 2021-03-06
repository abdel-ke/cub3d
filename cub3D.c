/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:33:41 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/12 18:04:37 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	initial_player(t_data *d)
{
	d->p.rad = TILE_SIZE * 10 / 100 * MINI_MAP;
	d->num_rays = d->parse.p_w;
	d->p.rot_an = M_PI;
	d->p.mv_spd = 5.0;
	d->p.rot_spd = 2 * (M_PI / 180);
	d->nbr_spr = 0;
	d->p.walk_dir = 0;
	d->p.st_side = 0;
	d->p.turn_dir = 0;
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
	d->multiplayer = 0;
}

int		keypressed(int key, t_data *d)
{
	if (key == W_KEY)
		d->p.walk_dir = 1;
	if (key == S_KEY)
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

int		main(int ac, char **av)
{
	t_data t;

	err_handler(ac, av, &t.parse);
	initial_player(&t);
	t.mlx.mlx_ptr = mlx_init();
	if (t.parse.handle == 0)
		t.mlx.win_ptr = mlx_new_window(t.mlx.mlx_ptr, t.parse.p_w, t.parse.p_h,
		"Cub3d");
	t.load_img = mlx_new_image(t.mlx.mlx_ptr, t.parse.p_w, t.parse.p_h);
	t.load_data = (int *)mlx_get_data_addr(t.load_img, &t.mlx.bits_per_pixel,
	&t.mlx.size_line, &t.mlx.endian);
	main_texture(&t);
	draw(&t);
	if (t.parse.handle == 0)
	{
		mlx_hook(t.mlx.win_ptr, 2, (1L << 0), keypressed, &t);
		mlx_hook(t.mlx.win_ptr, 3, (1L >> 0), keyrealease, &t);
		mlx_hook(t.mlx.win_ptr, 17, (1L << 5), &close_win, &t);
		mlx_loop_hook(t.mlx.mlx_ptr, draw, &t);
		mlx_loop(t.mlx.mlx_ptr);
	}
	return (0);
}
