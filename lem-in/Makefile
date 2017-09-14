# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/23 17:08:13 by fbonnin           #+#    #+#              #
#    Updated: 2017/07/23 17:08:18 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

NAMES = \
main \
line \
input \
node \
neighbor \
parsing \
pathfinding \
move1 \
move2

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	cd libft && make
	gcc $(O_FILES) libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	cd libft && make clean
	rm -f $(O_FILES)

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

re: fclean all
