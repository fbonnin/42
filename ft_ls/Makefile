NAME = ft_ls

NAMES = \
main \
ls \
print_file \
get_dirents \
sort_dirents

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	cd src/libft && make
	gcc $(O_FILES) src/libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	cd src/libft && make clean
	rm -f $(O_FILES)

fclean: clean
	cd src/libft && make fclean
	rm -f $(NAME)

re: fclean all
