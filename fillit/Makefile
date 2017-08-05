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

SRCS =  srcs/can_put.c \
		srcs/clear_grid.c \
		srcs/create_grid.c \
		srcs/fill.c \
		srcs/find_min_square.c \
		srcs/get_splited_file.c \
		srcs/get_tetri.c \
		srcs/parse_all_tetri.c \
		srcs/print_grid.c \
		srcs/put_remove.c \
		srcs/scale_tetri.c \
		srcs/tetri_is_valide.c \
		srcs/tetri_match_rules.c \
		srcs/main.c

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
