int				get_nb_dirents(DIR *dir, int _a)
{
	int				result;
	struct dirent	*dirent;

	result = 0;
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (dirent->d_name[0] != '.' || _a)
			result++;
		dirent = readdir(dir);
	}
	return (result);
}

struct dirent	**get_dirents(DIR *dir, int nb_dirents, int _a)
{
	struct dirent	**dirents;
	int				i;
	struct dirent	*dirent;

	dirents = malloc(nb_dirents * sizeof(struct dirent *));
	i = 0;
	dirent = readdir(dir);
	while (dirent != NULL && i < nb_dirents)
	{
		if (dirent->d_name[0] != '.' || _a)
		{
			dirents[i] = dirent;
			i++;
		}
		dirent = readdir(dir);
	}
	return (dirents);
}
