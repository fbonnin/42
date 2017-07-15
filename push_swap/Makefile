# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/07 17:41:08 by fbonnin           #+#    #+#              #
#    Updated: 2017/06/07 17:41:48 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	cd checker_sources && make
	mv checker_sources/checker .
	cd push_swap_sources && make
	mv push_swap_sources/push_swap .

checker:
	cd checker_sources && make
	mv checker_sources/checker .

push_swap:
	cd push_swap_sources && make
	mv push_swap_sources/push_swap .

clean:
	cd libft && make clean
	cd checker_sources && make clean
	cd push_swap_sources && make clean

fclean:
	cd libft && make fclean
	cd checker_sources && make fclean
	rm -f checker
	cd push_swap_sources && make fclean
	rm -f push_swap

re: fclean all
