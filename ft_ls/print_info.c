

void print_info(struct stat info)
{
	mode_t m;

	m = info.st_mode;

	printf(m & S_IRUSR ? "r" : "-");
	printf(m & S_IWUSR ? "w" : "-");
	printf(m & S_IXUSR ? "x" : "-");
	printf(m & S_IRGRP ? "r" : "-");
	printf(m & S_IWGRP ? "w" : "-");
	printf(m & S_IXGRP ? "x" : "-");
	printf(m & S_IROTH ? "r" : "-");
	printf(m & S_IWOTH ? "w" : "-");
	printf(m & S_IXOTH ? "x" : "-");
}

void print_type(mode_t m)
{	
	if (S_ISREG(m))
		ft_printf("-");
	else if (S_ISBLK(m))
		ft_printf("b");
	else if (S_ISCHR(m))
		ft_printf("c");
	else if (S_ISDIR(m))
		ft_printf("d");
	else if (S_ISLNK(m))
		ft_printf("l");
	else if (S_ISFIFO(m))
		ft_printf("p");
	else if (S_ISSOCK(m))
		ft_printf("s");
}
