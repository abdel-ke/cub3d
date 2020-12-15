#include "cube.h"

void initial_player(t_data *t)
{
	t->player.radius = TILE_SIZE * 10 / 100 * MINI_MAP;
	/* t->player.turnDirection = 0;
	t->player.walkDirection = 0;
	t->player.step_to_side_left = 0;
	t->player.step_to_side_right = 0; */
	t->player.rotationAngle = M_PI; //0.5235987756;
	t->player.moveSpeed = 5.0;
	t->player.rotationSpeed = 2 * (M_PI / 180);
	t->nbr_spr = 0;
	t->raycast.dist_ray = (int *)malloc(sizeof(t->raycast.dist_ray) * WINDOW_WIDTH);
	find_player(t);
	// puts("ok");
}

void ddaa(t_data *t, int X0, int Y0, int X1, int Y1)
{
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate steps required for generating pixels
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// calculate increment in x & y for each steps
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= steps; i++)
	{
		t->load_data[(int)Y * WINDOW_WIDTH + (int)X] = 0xf00f0f;
		// mlx_pixel_put(t->mlx.mlx_ptr, t->mlx.win_ptr, X, Y, 0xF54561);
		// putpixel (X,Y,RED);  // put pixel at (X,Y)
		X += Xinc; // increment in x at each step
		Y += Yinc; // increment in y at each step
	}
}

int isWallAt(int x, int y)
{
	int mapx, mapy;
	mapx = x / TILE_SIZE;
	mapy = y / TILE_SIZE;
	if (map[mapy][mapx] == '1')
		return (1);
	if (map[mapy][mapx] == '2')
		return (2);
	return (0);
}

void update_player(t_data *t)
{
	t->player.rotationAngle += t->player.turnDirection * t->player.rotationSpeed;
	double moveStep;
	double moveStep1;
	double newPlayerX;
	double newPlayerY;

	if (t->player.walkDirection != 0)
	{
		moveStep = t->player.walkDirection * t->player.moveSpeed;
		newPlayerX = t->player.player_x + cos(t->player.rotationAngle) * moveStep;
		newPlayerY = t->player.player_y + sin(t->player.rotationAngle) * moveStep;
	}
	if (t->player.step_to_side != 0)
	{
		moveStep1 = t->player.step_to_side * t->player.moveSpeed;
		newPlayerX = t->player.player_x + cos(t->player.rotationAngle - (90 * M_PI / 180)) * moveStep1;
		newPlayerY = t->player.player_y + sin(t->player.rotationAngle - (90 * M_PI / 180)) * moveStep1;
	}

	if (!isWallAt(t->player.player_x, newPlayerY))
		t->player.player_y = newPlayerY;
	if (!isWallAt(newPlayerX, t->player.player_y))
		t->player.player_x = newPlayerX;

	/* if (!isWallAt(newPlayerX, newPlayerY))
	{
		t->player.player_x = newPlayerX;
		t->player.player_y = newPlayerY;
	} */
	// find_sprit(t);
}

void circle(t_data *t, int tileX, int tileY)
{
	double a = 0, x, y;
	while (a <= M_PI * 2)
	{
		x = t->player.radius * cos(a) + tileX * MINI_MAP;
		y = t->player.radius * sin(a) + tileY * MINI_MAP;
		// mlx_pixel_put(t->mlx.mlx_ptr, t->mlx.win_ptr, x, y, 0xff00ff);
		t->load_data[(int)y * WINDOW_WIDTH + (int)x] = 0xff0000;
		a += 0.01;
	}
}

int keyPressed(int key, t_data *t)
{
	t->player.walkDirection = 0;
	t->player.turnDirection = 0;
	t->player.step_to_side = 0;
	if (key == UP_KEY) // up
		t->player.walkDirection = 1;
	if (key == DOWN_KEY) // down
		t->player.walkDirection = -1;
	if (key == RIGHT_KEY) //Right
		t->player.turnDirection = 1;
	if (key == LEFT_KEY) //Left
		t->player.turnDirection = -1;
	if (key == A_KEY)
		t->player.step_to_side = +1;
	if (key == D_KEY)
		t->player.step_to_side = -1;
	if (key == QUIT_KEY) // Exit
		exit(0);
	//Draw(t);
	return (0);
}

int keyRealease(int key, t_data *t)
{
	if (key == UP_KEY) // up
		t->player.walkDirection = 0;
	if (key == DOWN_KEY) // down
		t->player.walkDirection = 0;
	if (key == RIGHT_KEY) //Right
		t->player.turnDirection = 0;
	if (key == LEFT_KEY) //Left
		t->player.turnDirection = 0;
	if (key == A_KEY)
		t->player.step_to_side = 0;
	if (key == D_KEY)
		t->player.step_to_side = 0;
	// if (key == QUIT_KEY) // Exit
	// exit(0);
	// Draw(t);
	return (0);
}

void put_player(t_data *t, int i, int j, double rotation)
{
	t->player.rotationAngle = rotation;
	t->player.player_y = i * TILE_SIZE + TILE_SIZE / 2;
	t->player.player_x = j * TILE_SIZE + TILE_SIZE / 2;
}

int	number_sprite(t_data *t)
{
return (0);
}

void find_player(t_data *t)
{
	int i;
	int j;
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == 'N')
				put_player(t, i, j, 3 * M_PI / 2);
			else if (map[i][j] == 'W')
				put_player(t, i, j, M_PI);
			else if (map[i][j] == 'E')
				put_player(t, i, j, 0);
			else if (map[i][j] == 'S')
				put_player(t, i, j, M_PI / 2);
			else if (map[i][j] == '2')
				t->nbr_spr++;
			j++;
		}
		i++;
	}
	stock_pos_spr(t);
}

void sky_floor_color(t_data *t)
{
	int x = WINDOW_HEIGHT / 2 * WINDOW_WIDTH;
	int y = 0;

	while (y != x)
	{
		t->load_data[y] = 0x99ccff;
		t->load_data[x + y++] = 0xcd8500;
	}
}

int Draw(t_data *t)
{
	mlx_destroy_image(t->mlx.mlx_ptr, t->load_img);
	// mlx_clear_window(t->mlx.mlx_ptr, t->mlx.img_ptr);
	t->load_img = mlx_new_image(t->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_clear_window(t->mlx.mlx_ptr, t->mlx.win_ptr);
	update_player(t);
	sky_floor_color(t);
	castAllRays(t);
	draw_map(t);
	mlx_put_image_to_window(t->mlx.mlx_ptr, t->mlx.win_ptr, t->load_img, 0, 0);
	return 0;
}
