# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/18 13:48:13 by fbonnin           #+#    #+#              #
#    Updated: 2017/10/17 11:31:01 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

NAMES = \
main \
check_file \
load_file \
geometry \
calculations1 \
calculations2 \
draw_result \
mlx

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
