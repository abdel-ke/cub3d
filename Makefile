NAME = cube3d

NAMA = cub.a

SRC = 	main.c\
		map.c\
		player.c\
		raycaste.c\
		sprite.c\
		sprite_util.c\
		sprit.c\
		texture.c\
		#ft_atoi.c\
		ft_color.c\
		ft_error.c\
		ft_parcing_map_2.c\
		ft_parcing_map.c\
		ft_resolution.c\
		ft_split.c\
		ft_strtrim.c\
		ft_textures.c\
		get_next_line_utils.c\
		get_next_line.c\
		main.c\
		parse.c

OBJ=$(SRC:.c=.o)

CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAMA) $(OBJ)
	gcc $(CFLAGS) $(NAMA) -o $(NAME)
	@echo 'SUCCESS!'

clean:
	@rm -f $(OBJ) *.a

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAMA)

re: fclean all

