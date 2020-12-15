#ifndef CUBE_H
#define CUBE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

#define TSTA 1000
#define TSTB 800
#define TILE_SIZE 96
#define MAP_NUM_ROWS 11						  //11
#define MAP_NUM_COLS 15						  //15
#define WINDOW_WIDTH MAP_NUM_COLS * TILE_SIZE  // 15 * 32 = 480
#define WINDOW_HEIGHT MAP_NUM_ROWS * TILE_SIZE // 11 * 32 = 352

#define UP_KEY 126	  //126
#define DOWN_KEY 125  //125
#define RIGHT_KEY 124 //124
#define LEFT_KEY 123  //123
#define Q_KEY 13	  //23
#define S_KEY 1		  //1
#define D_KEY 2		  //2
#define A_KEY 0		  //0
#define QUIT_KEY 53	  //53

#define N 0
#define S 1
#define W 2
#define E 3

#define FOV_ANGLE 60 * (M_PI / 180)				 //1.04719755
#define WALL_STRIP_WIDTH 1						 //5
#define NUM_RAYS WINDOW_WIDTH / WALL_STRIP_WIDTH // 15 * 32 = 480

#define MINI_MAP 0.2

typedef struct s_mlx
{
	void *win_ptr;
	void *mlx_ptr;

	int	*data_adress;
	void *img_ptr;
	int bits_per_pixel;
	int size_line;
	int endian;
} t_mlx;

typedef struct s_player
{
	int radius;
	int step_to_side;
	int turnDirection;	  // -1 if left, +1 if right
	int walkDirection;	  // -1 if back, +1 if front
	double rotationAngle; //M_PI / 2
	double moveSpeed;	  // 2.0
	double rotationSpeed; // 0.5 * (Math.PI / 180);

	double player_x;
	double player_y;
} t_player;

typedef struct s_raycast
{
	double rayangle;	// normalizeAngle();
	double wallHitX;	// 0
	double wallHitY;	//0
	double distance;	//0
	int washitvertical; // false 0

	double israyfacingdown; //  rayangle > 0 && rayangle < M_PI;
	double israyfacingup;	// !isRayFacingDown;

	double israyfacingright; // rayangle > 3 * M_PI / 2|| rayangle < M_PI / 2;
	double israyfacingleft;	 // !isRayFacingRight

	double xstep;
	double ystep;
	double xintercept;
	double yintercept;
	double nexthorztouchx;
	double nexthorztouchy;
	double founhorzwallhit;
	double founvertwallhit;
	double horzwallhitx;
	double horzwallhity;
	double vertwallhitx;
	double vertwallhity;

	double nextverttouchx;
	double nextverttouchy;

	double horzhitdistance;
	double verthitdistance;

	double raydistance;
	double distancebprojectionplane;
	double wallstripheight;
	int *dist_ray;
} t_raycast;

typedef struct s_texture
{

	void *img;

	int	*data;

	int height;
	int width;

	int bits_per_pixel;
	int size_line;
	int endian;
	// int index;
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

	double spr_x;
	double spr_y;
	double dist_x;
	double sprite_angle;
	double ag;
	double x_star_wind;
	int nbr_sprr;
	int end;
}				t_sprite;

typedef struct data
{
	t_texture txt;
	t_mlx mlx;
	t_player player;
	t_raycast raycast;
	t_sprite *spr;
	int index;
	int	*load_data;
	void *load_img;
	int nbr_spr;
} t_data;

char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '2', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '2', '0', '0', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '0', '1'},
	{'1', '0', '2', '0', '0', '0', 'N', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

void initial_player(t_data *t);
void update_player(t_data *t);
int Draw(t_data *t);
void find_player(t_data *t);
void square(t_data *t, int tileX, int tileY);
void draw_map(t_data *t);
void circle(t_data *t, int tileX, int tileY);
void ddaa(t_data *t, int X0, int Y0, int X1, int Y1);
int keyPressed(int key, t_data *t);

//raycast
void cast(t_data *t);
void castAllRays(t_data *t); //, double rayangle);
double hasWallAt(double x, double y);
double normalizeAngle(double angle);
int isWallAt(int x, int y);
void render3DProjectedWalls(t_data *t, int i);

double	distanceBetweenPoints(double x1, double y1, double x2, double y2);
void	dist_to_spr(t_data *t);
// void find_sprits(t_data *t), int i, int j);

void	find_sprit(t_data *cube);
void	ft_sort_sprite(t_data *cube, double spx, double spy, int count);
double	ft_diffangle(double diffangle);
int		sprite_visible(t_data *cube, int sprite_indice);
void	found_sprite_angle(t_data *cube, int i);
void	drow_strips(t_data *t, int s_x, int i, int x);
void	drowsprite(t_data *cube, int i);
void	draw_sprite(t_data *cube, int count);
void	find_sprit(t_data *cube);

void main_texture(t_data *t);
void stock_pos_spr(t_data *t);
#endif
