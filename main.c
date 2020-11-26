#include "cube.h"
#include "map.c"
#include "player.c"
#include "raycaste.c"
// #include "texture.c"

int main()
{
	t_data t;
	initial_player(&t);

	t.mlx.mlx_ptr = mlx_init();
	t.mlx.win_ptr = mlx_new_window(t.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "one");
	t.txt.load_img = mlx_new_image(t.mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	t.txt.load_data = (int *)mlx_get_data_addr(t.txt.load_img, &t.txt.bits_per_pixel,
	&t.txt.size_line, &t.txt.endian);
	t.txt.img = mlx_xpm_file_to_image(t.mlx.mlx_ptr, "image/wall.xpm", &t.txt.width, &t.txt.height);
	t.txt.data = (int *)mlx_get_data_addr(t.txt.img, &t.txt.bits_per_pixel,
										   &t.txt.size_line, &t.txt.endian);
	Draw(&t);
	mlx_put_image_to_window(t.mlx.mlx_ptr, t.mlx.win_ptr, t.txt.load_img, 0, 0);
	mlx_hook(t.mlx.win_ptr, 2, (1L << 0), keyPressed, &t);
	mlx_hook(t.mlx.win_ptr, 3, (1L >> 0), keyRealease, &t);
	// mlx_loop_hook(t.mlx.mlx_ptr, Draw, &t);
	mlx_loop(t.mlx.mlx_ptr);
	return (0);
}
