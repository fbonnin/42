NAME = asm

NAMES = \
main \
bytecode \
line \
strings \
instruction \
parsing1 \
parsing2 \
declaration \
call \
op

O_FILES = $(addsuffix .o, $(NAMES))

$(NAME): $(O_FILES)
	cd libft && make
	gcc $(O_FILES) libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@

clean:
	cd libft && make clean
	rm -f $(O_FILES)

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

re: fclean all
