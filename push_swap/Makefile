all:
	cd checker_sources && make
	mv checker_sources/checker .

checker:
	cd checker_sources && make
	mv checker_sources/checker .

clean:
	cd libft && make clean
	cd checker_sources && make clean

fclean:
	cd libft && make fclean
	cd checker_sources && make fclean
	rm -f checker

re: fclean all
