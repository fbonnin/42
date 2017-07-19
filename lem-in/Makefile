NAME = lem-in

NAMES = \
main \
line \
input \
node \
neighbor \
parsing \
pathfinding \
move1 \
move2

O_FILES = $(addsuffix .o, $(NAMES))

$(NAME): $(O_FILES)
	cd libft && make
	gcc $(O_FILES) libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	cd libft && make clean
	rm -f $(O_FILES)

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

re: fclean all
