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

