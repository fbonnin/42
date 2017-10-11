# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/06 16:19:59 by fbonnin           #+#    #+#              #
#    Updated: 2017/10/06 16:20:01 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

NAMES = \
main \
ls \
get_elems \
print_elems \
info \
alloc_table \
table \
get_row \
sort_elems \
other

O_FILES = $(addprefix src/, $(addsuffix .o, $(NAMES)))

$(NAME): $(O_FILES)
	cd src/libft && make
	gcc $(O_FILES) src/libft/libft.a -o $(NAME)

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
