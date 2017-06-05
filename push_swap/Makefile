CHECKER_NAME = checker

CHECKER_NAMES = \
checker \
check_numbers \
list1 \
list2 \
list3 \
check_operations

CHECKER_FILES = $(addprefix checker/, $CHECKER_NAMES))

ALL_FILES = \
$(CHECKER_FILES)

O_FILES = $(addsuffix .o, $(ALL_FILES))

$(CHECKER_NAME): $(O_FILES)
	cd libft && make
	gcc $(O_FILES) libft/libft.a -o $(CHECKER_NAME)

all: $(CHECKER_NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	cd libft && make clean

fclean: clean
	cd libft && make fclean
	rm -f $(CHECKER_NAME)

re: fclean all
