#ifndef CUBE_H
#define CUBE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

#define TILE_SIZE 64
#define MAP_NUM_ROWS 11						  //11
#define MAP_NUM_COLS 15						  //15
#define WINDOW_WIDTH MAP_NUM_COLS *TILE_SIZE  // 15 * 32 = 480
#define WINDOW_HEIGHT MAP_NUM_ROWS *TILE_SIZE // 11 * 32 = 352

#define UP_KEY 126	  //126
#define DOWN_KEY 125  //125
#define RIGHT_KEY 2//124 //124
#define LEFT_KEY 0//123  //123
#define Q_KEY 13	  //23
#define S_KEY 1		  //1
#define D_KEY 124		  //2
#define A_KEY 123//0		  //0
#define QUIT_KEY 53	  //53

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

} t_raycast;

typedef struct s_texture
{
	void *load_img;
	void *img;

	int	*load_data;
	int	*data;

	int height;
	int width;

	int bits_per_pixel;
	int size_line;
	int endian;
}				t_texture;

typedef struct data
{
	t_texture txt;
	t_mlx mlx;
	t_player player;
	t_raycast raycast;
} t_data;

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void initial_player(t_data *t);
void update_player(t_data *t);
void Draw(t_data *t);
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
#endif
