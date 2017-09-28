void	sort_dirents(struct dirent **dirents, int nb_dirents, int _t, int _r)
{
	if (_t)
		sort_dirents_2(dirents, nb_dirents, is_lower_mtime, _r);
	else
		sort_dirents_2(dirents, nb_dirents, is_lower_name, _r);
}

void	sort_dirents_2(struct dirent **dirents, int nb_dirents,
int (*is_lower)(struct dirent *dirent1, struct dirent *dirent2), int _r)
{
	int				i;
	int				j;
	struct dirent	*dirent;

	i = 1;
	while (i < nb_dirents)
	{
		j = i;
		while (j > 0 && (
		(!_r && is_lower(dirents[j], dirents[j - 1]) ||
		(_r && is_lower(dirents[j - 1], dirents[j]))))
		{
			dirent = dirents[j - 1];
			dirents[j - 1] = dirents[j];
			dirents[j] = dirent;
			j--;
		}
		i++;
	}
}

int		is_lower_name(struct dirent *dirent1, struct dirent *dirent2)
{
	return (ft_strcmp(dirent1->d_name, dirent2->d_name) < 0);
}

int		is_lower_mtime(struct dirent *dirent1, struct dirent *dirent2)
{
	struct stat stat1;
	struct stat stat2;
	stat(dirent1->d_name, &stat1);
	stat(dirent2->d_name, &stat2);
	return (stat1.st_mtime > stat2.st_mtime);
}
