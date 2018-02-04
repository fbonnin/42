NAME = download.a

NAMES = \
download_pdf \
parseA \
parseB

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	ar rc $(NAME) $(O_FILES) tools.o

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c ../tools/tools.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	rm -f $(O_FILES) tools.o

fclean: clean
	rm -f $(NAME)

re: fclean all
