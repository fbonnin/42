NAME = download.a

NAMES = \
download_pdf \
parseA \
parseB

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	ar rc $(NAME) $(O_FILES) ../parsing/parsing.a

all: $(NAME) $(O_FILES)
%.o: %.c
	cd ../parsing && make
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	cd ../parsing && make clean
	rm -f $(O_FILES)

fclean: clean
	cd ../parsing && make fclean
	rm -f $(NAME)

re: fclean all
