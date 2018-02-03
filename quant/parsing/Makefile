NAME = parse_pdf.a

NAMES = \
parse_pdf \
notification \
tools_file \
extract_data \
tools_parsing

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	ar rc $(NAME) $(O_FILES)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
