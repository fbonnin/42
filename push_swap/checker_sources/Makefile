# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/07 17:35:20 by fbonnin           #+#    #+#              #
#    Updated: 2017/06/07 17:35:27 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

NAMES = \
checker \
get_numbers \
check_operations \
list1 \
list2 \
list3

O_FILES = $(addsuffix .o, $(NAMES))

$(NAME): $(O_FILES)
	cd ../libft && make
	gcc $(O_FILES) ../libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@ -Wall -Werror -Wextra

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
