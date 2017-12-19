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
	cd checker_src && make
	mv checker_src/checker .
	cd push_swap_src && make
	mv push_swap_src/push_swap .

checker:
	cd checker_src && make
	mv checker_src/checker .

push_swap:
	cd push_swap_src && make
	mv push_swap_src/push_swap .

clean:
	cd libft && make clean
	cd checker_src && make clean
	cd push_swap_src && make clean

fclean:
	cd libft && make fclean
	cd checker_src && make fclean
	rm -f checker
	cd push_swap_src && make fclean
	rm -f push_swap

re: fclean all
