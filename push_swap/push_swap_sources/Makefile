NAME = push_swap

NAMES = \
push_swap \
check_numbers \
bubble_sort \
insertion_sort \
merge_sort \
list1 \
list2 \
list3

O_FILES = $(addsuffix .o, $(NAMES))

$(NAME): $(O_FILES)
	cd ../libft && make
	gcc $(O_FILES) ../libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
