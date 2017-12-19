# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/07 17:47:59 by fbonnin           #+#    #+#              #
#    Updated: 2017/06/07 19:51:28 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

NAMES = \
push_swap \
push_swap_2 \
get_numbers \
bubble_sort \
insertion_sort \
merge_sort \
merge_sort_2 \
selection_sort \
sort3 \
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
