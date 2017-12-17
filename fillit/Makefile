# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 17:02:02 by acorbeau          #+#    #+#              #
#    Updated: 2017/04/26 17:45:22 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit


FLAGS = -Wall -Werror -Wextra

SRCS =  src/can_put.c \
		src/clear_grid.c \
		src/create_grid.c \
		src/fill.c \
		src/find_min_square.c \
		src/get_splited_file.c \
		src/get_tetri.c \
		src/parse_all_tetri.c \
		src/print_grid.c \
		src/put_remove.c \
		src/scale_tetri.c \
		src/tetri_is_valide.c \
		src/tetri_match_rules.c \
		src/main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L./libft -lft

%.o: %.c
	gcc -c $(FLAGS) -o $@ $<

clean:
	make -C libft/ clean
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
