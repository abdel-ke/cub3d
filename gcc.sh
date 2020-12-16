gcc -c main.c; gcc -o demok main.o libmlx.a -lXext -lX11 -lm; ./demok
#gcc -c tst.c ; gcc -o demok tst.o  libmlx.a -lXext -lX11 -lm; ./demok
# rm ./a.out; gcc main.c -lmlx -framework OpenGl -framework AppKit && ./a.out
