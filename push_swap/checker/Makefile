NAME = checker

NAMES = \
checker \
check_numbers \
list1 \
list2 \
list3 \
check_operations

O_FILES = $(addsuffix .o, $(NAMES))

$(NAME): $(O_FILES)
	gcc $(O_FILES) ../libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
