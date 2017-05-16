NAME = fdf

FILES = \
	main \
	check_file \
	load_file \
	mlx \
	calculations1 \
	calculations2 \
	draw_result

O_FILES = $(addsuffix .o, $(FILES))

$(NAME): $(O_FILES)
	cd libft && make
	gcc $(O_FILES) -o $(NAME)

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
