#include "cube.h"

/*void imag_put(t_data *t, int x, int y, int color)
{
	char *dst;
	dst = t->mlx.data_adress + y * (int)t->mlx.size_line + x * ((int)t->mlx.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}*/

void	square(t_data *t, int tileX, int tileY)
{
	int x;
	int y;

	x = 0;
	while (x <= TILE_SIZE * MINI_MAP)
	{
		y = 0;
		while (y <= TILE_SIZE * MINI_MAP)
		{
			t->load_data[(tileY + y) * t->win_w + (tileX + x)] = 0x0000ff;
			y++;
		}
		x++;
	}
}

void	draw_map(t_data *t)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			int tileX = j * TILE_SIZE * MINI_MAP;
			int tileY = i * TILE_SIZE * MINI_MAP;
			if (map[i][j] == '1')
				square(t, (int)tileX, (int)tileY);
			j++;
		}
		i++;
	}
	circle(t, t->p.pl_x, t->p.pl_y);
}
