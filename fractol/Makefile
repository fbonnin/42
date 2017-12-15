# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/15 18:53:32 by fbonnin           #+#    #+#              #
#    Updated: 2017/12/15 18:53:34 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

NAMES = \
mlx \
main \
general \
iterate \
display \
colors \
events \
keyboard \
zoom

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	cd src/libft && make
	gcc $(O_FILES) src/libft/libft.a -o $(NAME) -lmlx -framework OpenGL -framework AppKit

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	cd src/libft && make clean
	rm -f $(O_FILES)

fclean: clean
	cd src/libft && make fclean
	rm -f $(NAME)

re: fclean all
