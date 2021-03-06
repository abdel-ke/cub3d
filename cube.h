/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:24:51 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/12 18:02:14 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include "parcing/cub.h"
# define TILE_SIZE 64
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define A_KEY 0
# define QUIT_KEY 53
# define N 0
# define S 1
# define W 2
# define E 3
# define FOV_ANGLE 1.0471975512
# define MINI_MAP 0.1

typedef struct	s_mlx
{
	void		*win_ptr;
	void		*mlx_ptr;
	int			*data_adress;
	void		*img_ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct	s_player
{
	int			rad;
	int			st_side;
	int			turn_dir;
	int			walk_dir;
	double		rot_an;
	double		mv_spd;
	double		rot_spd;
	double		pl_x;
	double		pl_y;
}				t_player;

typedef struct	s_raycast
{
	double		rayangle;
	double		wallhit_x;
	double		wallhit_y;
	double		dist;
	int			was_hitvert;
	double		is_ray_down;
	double		is_ray_up;
	double		is_ray_right;
	double		is_ray_lft;
	double		xstep;
	double		ystep;
	double		xintercept;
	double		yintercept;
	double		nexthorztouchx;
	double		nexthorztouchy;
	double		founhorzwallhit;
	double		founvertwallhit;
	double		horzwallhit_x;
	double		horzwallhit_y;
	double		vertwallhit_x;
	double		vertwallhit_y;
	double		nextverttouchx;
	double		nextverttouchy;
	double		horzhitdist;
	double		verthitdist;
	double		raydist;
	double		distbprojectplane;
	double		wallstripheight;
	int			*dist_ray;
}				t_raycast;

typedef struct	s_texture
{
	void		*img;
	int			*data;
	int			height;
	int			width;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_texture[5];

typedef struct	s_sprite
{
	void		*img_spr;
	int			*data_spr;
	int			height;
	int			height1;
	int			width;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	double		spr_x;
	double		spr_y;
	double		dist_x;
	double		spr_angle;
	double		ag;
	double		x_star_wind;
	int			nbr_sprr;
	int			end;
}				t_sprite;

typedef struct	s_dda
{
	int			dx;
	int			dy;
	int			steps;
	float		xinc;
	float		yinc;
	float		x;
	float		y;
}				t_dda;

typedef struct	s_render
{
	int			start;
	int			end;
	int			xtex;
	int			ytex;
	int			color;
}				t_render;

typedef struct	s_data
{
	t_texture	txt;
	t_mlx		mlx;
	t_player	p;
	t_raycast	r_cst;
	t_sprite	*spr;
	t_dda		dda;
	t_render	rndr;
	t_parcing	parse;
	int			index;
	int			*load_data;
	void		*load_img;
	int			nbr_spr;
	int			win_h;
	int			win_w;
	double		num_rays;
	int			multiplayer;
}				t_data;

void			initial_player(t_data *t);
void			update_player(t_data *t);
int				draw(t_data *t);
void			find_player(t_data *t);
int				keypressed(int key, t_data *t);
void			cast(t_data *t);
void			castallrays(t_data *t);
double			normalizeangle(double angle);
int				iswallat(t_data *d, int x, int y);
void			render3dprojectedwalls(t_data *t, int i, int j);
double			distbetweenpoints(double x1, double y1, double x2, double y2);
void			dist_to_spr(t_data *t);
void			ft_sort_sprite(t_data *cube, double spx, double spy, int count);
double			ft_diffangle(double diffangle);
int				sprite_visible(t_data *cube, int sprite_indice);
void			found_spr_angle(t_data *cube, int i);
void			drow_strips(t_data *t, int s_x, int i, int x);
void			drowsprite(t_data *cube, int i);
void			draw_sprite(t_data *cube, int count);
void			find_sprit(t_data *cube);
void			main_texture(t_data *t);
void			stock_pos_spr(t_data *t);
void			sky_floor_color(t_data *d);
void			put_player(t_data *d, int i, int j, double rotation);
int				keyrealease(int key, t_data *t);
int				close_win();
void			find_horz_wall(t_data *d);
void			find_vert_wall(t_data *d);
int				is_text_up_down(t_data *d);
int				is_text_left_right(t_data *d);
void			init_ray(t_data *d);
void			calculate(t_data *d);
int				was_hitvert(t_data *d);
void			find_horizontall_wall(t_data *d);
void			find_vertical_wall(t_data *d);
void			render3dprojectedwalls(t_data *d, int i, int j);
void			err_handler(int ac, char **av, t_parcing *p);
void			ft_save(t_data *d);
int				ft_check_save(char *str);
void			ft_free2(t_data *p);
#endif
