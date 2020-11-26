#include "cube.h"

/*void imag_put(t_data *t, int x, int y, int color)
{
	char *dst;
	dst = t->mlx.data_adress + y * (int)t->mlx.size_line + x * ((int)t->mlx.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}*/

void	square(t_data *t, int tileX, int tileY)
{
	int x = 0, y;
	while (x <= TILE_SIZE * MINI_MAP)
	{
		y = 0;
		while (y <= TILE_SIZE * MINI_MAP)
		{
			// mlx_pixel_put(t->mlx.mlx_ptr, t->mlx.win_ptr, x + tileX, y + tileY, 0xffffff);
			t->txt.load_data[(tileY + y) * WINDOW_WIDTH + (tileX + x)] = 0x0000ff;
			// imag_put(t, x, y, 0xffffff);
			y++;
		}
		x++;
	}
}

void	draw_map(t_data *t)
{
	int i, j;
	for (i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE * MINI_MAP;
			int tileY = i * TILE_SIZE * MINI_MAP;
			if (map[i][j] == 1)
				square(t, (int)tileX, (int)tileY);
		}
	}
	circle(t, t->player.player_x, t->player.player_y);
}