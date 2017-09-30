#include "ls.h"

void print_file(char *name, int _l)
{
	struct stat info;
	int			i;

	if (_l)
	{
		stat(name, &info);
		print_info(info);
	}
	i = ft_strlen(name);
	while (i > 0 && name[i - 1] != '/')
		i--;
	ft_printf(1, "%s\n", name + i);
}

void print_info(struct stat info)
{
	mode_t			m;
	struct passwd	*user;
	struct group	*group;
	char			*date;

	ft_printf(1, "%d %d ", major(info.st_rdev), minor(info.st_rdev));
	m = info.st_mode;
	print_type(m);
	print_permissions(m);
	ft_printf(1, " ");
	ft_printf(1, "%lu ", info.st_nlink);
	user = getpwuid(info.st_uid);
	ft_printf(1, "%s ", user->pw_name);
	group = getgrgid(info.st_gid);
	ft_printf(1, "%s ", group->gr_name);
	ft_printf(1, "%ld ", info.st_size);
	date = ctime(&info.st_mtime) + 4;
	date[12] = 0;
	ft_printf(1, "%s ", date);
	free(date - 4);
}

void print_type(mode_t m)
{	
	if (S_ISREG(m))
		ft_printf(1, "-");
	else if (S_ISBLK(m))
		ft_printf(1, "b");
	else if (S_ISCHR(m))
		ft_printf(1, "c");
	else if (S_ISDIR(m))
		ft_printf(1, "d");
	else if (S_ISLNK(m))
		ft_printf(1, "l");
	else if (S_ISFIFO(m))
		ft_printf(1, "p");
	else if (S_ISSOCK(m))
		ft_printf(1, "s");
}

void print_permissions(mode_t m)
{
	ft_printf(1, m & S_IRUSR ? "r" : "-");
	ft_printf(1, m & S_IWUSR ? "w" : "-");
	ft_printf(1, m & S_IXUSR ? "x" : "-");
	ft_printf(1, m & S_IRGRP ? "r" : "-");
	ft_printf(1, m & S_IWGRP ? "w" : "-");
	ft_printf(1, m & S_IXGRP ? "x" : "-");
	ft_printf(1, m & S_IROTH ? "r" : "-");
	ft_printf(1, m & S_IWOTH ? "w" : "-");
	ft_printf(1, m & S_IXOTH ? "x" : "-");
}

void print_elems(char **elems, int nb_elems, int _l)
{
	int i;

	i = 0;
	while (i < nb_elems)
	{
		print_file(elems[i], _l);
		i++;
	}
}
