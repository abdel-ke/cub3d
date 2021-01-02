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
}				t_texture;


int main()
{
	t_texture t;
	void * mlx_ptr;
	void * win_ptr;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "TEST IMAGE");

	t.load_img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	t.load_data = (int *)mlx_get_data_addr(t.load_img, &t.bits_per_pixel,
	&t.size_line, &t.endian);

	t.img = mlx_xpm_file_to_image(mlx_ptr, "image/wall.XPM", &t.width,
										  &t.height);
	t.data = (int *)mlx_get_data_addr(t.img, &t.bits_per_pixel,
											  &t.size_line, &t.endian);
	int i = 0, j;
	while (i < 150)
	{
		j = 0;
		while (j < 150)
		{
			t.load_data[(WINDOW_WIDTH * j) + i] = t.data[i * t.width + j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, t.load_img, 0, 0);
	mlx_loop(mlx_ptr);
}
