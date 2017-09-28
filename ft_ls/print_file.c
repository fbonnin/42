void print_file(char *name, int _l)
{
	struct stat info;

	if (_l)
	{
		stat(name, &info);
		print_info(info);
	}
	ft_printf("%s\n", name);
}

void print_info(struct stat info)
{
	mode_t			m;
	struct passwd	*user;
	struct group	*group;
	char			*date;

	m = info.st_mode;
	print_type(m);
	print_permissions(m);
	ft_printf(" ");
	ft_printf("%lu ", info.st_nlink);
	user = getpwuid(info.st_uid);
	ft_printf("%s ", user->pw_name);
	group = getgrgid(info.st_gid);
	ft_printf("%s ", user->gr_name);
	ft_printf("%ld ", info.st_size);
	date = ctime(&info.st_mtime) + 4;
	date[12] = 0;
	ft_printf("%s ", date);
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

void print_permissions(mode_t m)
{
	ft_printf(m & S_IRUSR ? "r" : "-");
	ft_printf(m & S_IWUSR ? "w" : "-");
	ft_printf(m & S_IXUSR ? "x" : "-");
	ft_printf(m & S_IRGRP ? "r" : "-");
	ft_printf(m & S_IWGRP ? "w" : "-");
	ft_printf(m & S_IXGRP ? "x" : "-");
	ft_printf(m & S_IROTH ? "r" : "-");
	ft_printf(m & S_IWOTH ? "w" : "-");
	ft_printf(m & S_IXOTH ? "x" : "-");
}

void print_dirents(struct dirent **dirents, int nb_dirents, int _l)
{
	int i;

	i = 0;
	while (i < nb_dirents)
	{
		print_file(dirents[i]->d_name, _l);
		i++;
	}
}
