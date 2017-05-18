# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/18 13:48:13 by fbonnin           #+#    #+#              #
#    Updated: 2017/05/18 13:48:55 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FILES = \
	main \
	check_file \
	load_file \
	geometry \
	calculations1 \
	calculations2 \
	draw_result \
	mlx

O_FILES = $(addsuffix .o, $(FILES))

$(NAME): $(O_FILES)
	cd libft && make
	gcc $(O_FILES) libft/libft.a -o $(NAME) -lmlx -framework OpenGL -framework AppKit

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
