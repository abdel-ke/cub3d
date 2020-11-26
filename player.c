#include "cube.h"

void	initial_player(t_data *t)
{
	t->player.radius = TILE_SIZE * 10 / 100 * MINI_MAP;
	/* t->player.turnDirection = 0;
	t->player.walkDirection = 0;
	t->player.step_to_side_left = 0;
	t->player.step_to_side_right = 0; */
	t->player.rotationAngle = 0; //0.5235987756;
	t->player.moveSpeed = 5.0;
	t->player.rotationSpeed = 2 * (M_PI / 180);
	find_player(t);
}

void	ddaa(t_data *t, int X0, int Y0, int X1, int Y1)
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
		t->txt.load_data[(int)Y * WINDOW_WIDTH + (int)X] = 0xf00f0f;
		// mlx_pixel_put(t->mlx.mlx_ptr, t->mlx.win_ptr, X, Y, 0xF54561);
		// putpixel (X,Y,RED);  // put pixel at (X,Y)
		X += Xinc; // increment in x at each step
		Y += Yinc; // increment in y at each step
	}
}

int		isWallAt(int x, int y)
{
	int i, j;
	i = x / TILE_SIZE;
	j = y / TILE_SIZE;
	if (map[j][i] == 1)
		return (1);
	return (0);
}

void	update_player(t_data *t)
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

	if (!isWallAt(newPlayerX, newPlayerY))
	{
		t->player.player_x = newPlayerX;
		t->player.player_y = newPlayerY;
	}
}

void	circle(t_data *t, int tileX, int tileY)
{
	double a = 0, x, y;
	while (a <= M_PI * 2)
	{
		x = t->player.radius * cos(a) + tileX * MINI_MAP;
		y = t->player.radius * sin(a) + tileY * MINI_MAP;
		// mlx_pixel_put(t->mlx.mlx_ptr, t->mlx.win_ptr, x, y, 0xff00ff);
		t->txt.load_data[(int)y * WINDOW_WIDTH + (int)x] = 0xff0000;
		a += 0.01;
	}
}

int		keyPressed(int key, t_data *t)
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
	Draw(t);
	return (0);
}
int		keyRealease(int key, t_data *t)
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

void	find_player(t_data *t)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == 5)
			{
				t->player.player_y = i * TILE_SIZE + (TILE_SIZE / 2) * MINI_MAP;
				t->player.player_x = j * TILE_SIZE + (TILE_SIZE / 2) * MINI_MAP;
			}
			j++;
		}
		i++;
	}
}

void	sky_floor_color(t_data *t)
{
	int x = WINDOW_HEIGHT / 2 * WINDOW_WIDTH;
	int y = 0;

	while (y != x)
	{
		t->txt.load_data[y] = 0x99ccff;
		t->txt.load_data[x + y++] = 0xcd8500;
	}
}

void	Draw(t_data *t)
{
	mlx_destroy_image(t->mlx.mlx_ptr, t->txt.load_img);
	// mlx_clear_window(t->mlx.mlx_ptr, t->mlx.img_ptr);
	t->txt.load_img = mlx_new_image(t->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	t->txt.load_data = (int *)mlx_get_data_addr(t->txt.load_img, &t->txt.bits_per_pixel,
	&t->txt.size_line, &t->txt.endian);
	mlx_clear_window(t->mlx.mlx_ptr, t->mlx.win_ptr);
	update_player(t);
	sky_floor_color(t);
	castAllRays(t);
	draw_map(t);
	mlx_put_image_to_window(t->mlx.mlx_ptr, t->mlx.win_ptr, t->txt.load_img, 0, 0);
}
