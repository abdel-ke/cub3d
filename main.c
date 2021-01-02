#include "cube.h"
#include "map.c"
#include "player.c"
#include "raycaste.c"
#include "texture.c"
#include "sprit.c"
// #include "sprite.c"
// #include "sprite_util.c"

int close_win(t_data *t)
{
	exit(0);
	return (0);
}

int main()
{
	t_data t;
	initial_player(&t);

	t.mlx.mlx_ptr = mlx_init();
	t.mlx.win_ptr = mlx_new_window(t.mlx.mlx_ptr, t.win_w, t.win_h, "one");
	t.load_img = mlx_new_image(t.mlx.mlx_ptr, t.win_w, t.win_h);
	t.load_data = (int *)mlx_get_data_addr(t.load_img, &t.txt[0].bits_per_pixel,
												  &t.txt[0].size_line, &t.txt[0].endian);
	main_texture(&t);

	/* t.txt[0].img = mlx_xpm_file_to_image(t.mlx.mlx_ptr, "image/wall.XPM", &t.txt[0].width,
										 &t.txt[0].height);
	t.txt[0].data = (int *)mlx_get_data_addr(t.txt[0].img, &t.txt[0].bits_per_pixel,
											 &t.txt[0].size_line, &t.txt[0].endian); */

	Draw(&t);
	mlx_hook(t.mlx.win_ptr, 2, (1L << 0), keyPressed, &t);
	mlx_hook(t.mlx.win_ptr, 3, (1L >> 0), keyRealease, &t);
	mlx_hook(t.mlx.win_ptr, 17, 1L << 5, &close_win, &t);
	mlx_loop_hook(t.mlx.mlx_ptr, Draw, &t);
	mlx_loop(t.mlx.mlx_ptr);
	return (0);
}
