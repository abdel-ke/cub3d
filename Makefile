NAME = Cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS =  -lmlx -framework OpenGL -framework AppKit
SRC = 	main.c\
		map.c\
		player.c\
		raycaste.c\
		sprite_util.c\
		texture.c\
		sprit.c\
		keypress.c\
		cast.c\
		parcing/ft_atoi.c\
		parcing/ft_color.c\
		parcing/ft_error.c\
		parcing/ft_parcing_map_2.c\
		parcing/ft_parcing_map.c\
		parcing/ft_resolution.c\
		parcing/ft_split.c\
		parcing/ft_strtrim.c\
		parcing/ft_textures.c\
		parcing/get_next_line_utils.c\
		parcing/get_next_line.c\
		parcing/parse.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# %.o : %.c
# 	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

