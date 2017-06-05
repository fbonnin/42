CHECKER_NAME = checker

all:
	cd libft && make
	cd checker_sources && make
	mv checker_sources/checker checker

$(CHECKER_NAME):
	cd checker && make
	mv checker_sources/checker checker

clean:
	cd libft && make clean
	cd checker_sources && make clean

fclean:
	cd libft && make fclean
	cd checker_sources && make fclean

re: fclean all
