NAME = scraping

NAMES = \
main \
download/download_pdf \
download/parseA \
download/parseB \
parsing/parse_pdf \
parsing/notification \
parsing/extract_data \
tools

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	gcc $(O_FILES) -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
