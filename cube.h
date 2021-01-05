#ifndef CUBE_H
#define CUBE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

#define TILE_SIZE 96
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define UP_KEY 126
#define DOWN_KEY 125
#define RIGHT_KEY 124
#define LEFT_KEY 123
#define Q_KEY 13
#define S_KEY 1
#define D_KEY 2
#define A_KEY 0
#define QUIT_KEY 53
#define N 0
#define S 1
#define W 2
#define E 3
#define FOV_ANGLE 60 * (M_PI / 180)
#define WALL_STRIP_WIDTH 1
#define NUM_RAYS 1440 / WALL_STRIP_WIDTH
#define MINI_MAP 0.2

typedef struct s_mlx
{
	void	*win_ptr;
	void	*mlx_ptr;
	int		*data_adress;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
} t_mlx;

typedef struct s_player
{
	int		rad;
	int		st_side;
	int		turn_dir;
	int		walk_dir;
	double	rot_an;
	double	mv_spd;
	double	rot_spd;
	double	pl_x;
	double	pl_y;
} t_player;

typedef struct s_raycast
{
	double	rayangle;
	double	wallhit_x;
	double	wallhit_y;
	double	dist;
	int		was_hitvert;
	double	is_ray_down;
	double	is_ray_up;
	double	is_ray_right;
	double	is_ray_lft;
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;
	double	nexthorztouchx;
	double	nexthorztouchy;
	double	founhorzwallhit;
	double	founvertwallhit;
	double	horzwallhit_x;
	double	horzwallhit_y;
	double	vertwallhit_x;
	double	vertwallhit_y;
	double	nextverttouchx;
	double	nextverttouchy;
	double	horzhitdist;
	double	verthitdist;
	double	raydist;
	double	distbprojectplane;
	double	wallstripheight;
	int		*dist_ray;
} t_raycast;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_texture[5];

typedef struct s_sprite
{
	void	*img_spr;
	int		*data_spr;
	int		height;
	int		height1;
	int		width;
	int 	bits_per_pixel;
	int 	size_line;
	int 	endian;
	double	spr_x;
	double	spr_y;
	double	dist_x;
	double	spr_angle;
	double	ag;
	double	x_star_wind;
	int		nbr_sprr;
	int		end;
}				t_sprite;

typedef struct	s_dda
{
	int dx;
	int dy;
	int steps;
	float Xinc;
	float Yinc;
	float X;
	float Y;
}				t_dda;

typedef struct 	s_render
{
	int start;
	int end;
	int xtex;
	int ytex;
	int color;
}				t_render;

typedef struct data
{
	t_texture	txt;
	t_mlx		mlx;
	t_player	p;
	t_raycast	r_cst;
	t_sprite	*spr;
	t_dda		dda;
	t_render	rndr;
	int			index;
	int			*load_data;
	void		*load_img;
	int			nbr_spr;
	int			win_h;
	int			win_w;
	double		num_rays;
} t_data;

static char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '1', '0', '1'},
{'1', '0', '0', '0', '0', '1', '2', '0', '0', '0', '0', '0', '1', '0', '1'},
{'1', '1', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '1', '0', '1'},
{'1', '0', '0', '0', '0', '0', '2', '0', '0', '0', '1', '0', '1', '0', '1'},
{'1', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
{'1', '0', '0', '0', '0', '0', 'N', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
{'1', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

void	initial_player(t_data *t);
void	update_player(t_data *t);
int		draw(t_data *t);
void	find_player(t_data *t);
void	square(t_data *t, int tileX, int tileY);
void	draw_map(t_data *t);
void	circle(t_data *t, int tileX, int tileY);
void	ddaa(t_data *t, int X1, int Y1);
int		keypressed(int key, t_data *t);
void	cast(t_data *t);
void	castallrays(t_data *t);
double	hasWallAt(double x, double y);
double	normalizeangle(double angle);
int		iswallat(int x, int y);
void	render3dprojectedwalls(t_data *t, int i, int j);
double	distbetweenpoints(double x1, double y1, double x2, double y2);
void	dist_to_spr(t_data *t);
void	ft_sort_sprite(t_data *cube, double spx, double spy, int count);
double	ft_diffangle(double diffangle);
int		sprite_visible(t_data *cube, int sprite_indice);
void	found_spr_angle(t_data *cube, int i);
void	drow_strips(t_data *t, int s_x, int i, int x);
void	drowsprite(t_data *cube, int i);
void	draw_sprite(t_data *cube, int count);
void	find_sprit(t_data *cube);
void	main_texture(t_data *t);
void	stock_pos_spr(t_data *t);
void	sky_floor_color(t_data *d);
void	put_player(t_data *d, int i, int j, double rotation);

int		keyrealease(int key, t_data *t);
int		close_win();

void	find_horz_wall(t_data *d);
void	find_vert_wall(t_data *d);
int		is_text_up_down(t_data *d);
int		is_text_left_right(t_data *d);
void	init_ray(t_data *d);
void	calculate(t_data *d);
int		was_hitvert(t_data *d);
void	find_horizontall_wall(t_data *d);
void	find_vertical_wall(t_data *d);
void	draw_projected_wall(t_data *d, int i, int j);

#endif
