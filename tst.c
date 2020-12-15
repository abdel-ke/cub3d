#include <mlx.h>
#include <stdio.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

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
}				t_texture[5];


int main()
{
	t_texture t;
	void * mlx_ptr;
	void * win_ptr;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "one");
	t[0].load_img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	t[0].load_data = (int *)mlx_get_data_addr(t[0].load_img, &t[0].bits_per_pixel,
	&t[0].size_line, &t[0].endian);

	t[0].img = mlx_xpm_file_to_image(mlx_ptr, "image/wall.XPM", &t[0].width,
										  &t[0].height);
	t[0].data = (int *)mlx_get_data_addr(t[0].img, &t[0].bits_per_pixel,
											  &t[0].size_line, &t[0].endian);

	t[1].img = mlx_xpm_file_to_image(mlx_ptr, "image/1.XPM", &t[1].width,
										  &t[1].height);
	t[1].data = (int *)mlx_get_data_addr(t[1].img, &t[1].bits_per_pixel,
											  &t[1].size_line, &t[1].endian);
	int i = 0, j, z;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			// printf("%d\t%d\t%d\n", i, j, z);
			t[0].load_data[(WINDOW_WIDTH * j) + i] = t[0].data[i * t[0].width + j];
			// t[1].load_data[(WINDOW_WIDTH * j) + i + z] = t[1].data[i * t[1].width + j + z];
			j++;
		}
		i++;
	}
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			// printf("%d\t%d\t%d.\n", i, j, z);
			// t[0].load_data[(WINDOW_WIDTH * j) + i] = t[0].data[i * t[0].width + j];
			t[0].load_data[(WINDOW_WIDTH * j) + i] = t[1].data[i * t[1].width + j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, t[0].load_img, 0, 0);
	mlx_loop(mlx_ptr);

	// printf("%d\t%d", , min)
}
