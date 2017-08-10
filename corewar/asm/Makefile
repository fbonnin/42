# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/10 20:36:32 by fbonnin           #+#    #+#              #
#    Updated: 2017/08/10 20:36:33 by fbonnin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

NAMES = \
main \
bytecode \
line \
strings \
instruction \
parsing1 \
parsing2 \
declaration \
call \
op

O_FILES = $(addsuffix .o, $(addprefix src/, $(NAMES)))

$(NAME): $(O_FILES)
	cd src/libft && make
	gcc $(O_FILES) src/libft/libft.a -o $(NAME)

all: $(NAME) $(O_FILES)
%.o: %.c
	gcc -c $< -o $@

clean:
	cd src/libft && make clean
	rm -f $(O_FILES)

fclean: clean
	cd src/libft && make fclean
	rm -f $(NAME)

re: fclean all
