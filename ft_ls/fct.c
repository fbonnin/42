int				get_nb_dirents(DIR *dir)
{
	int				result;
	struct dirent	*dirent;

	result = 0;
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		result++;
		dirent = readdir(dir);
	}
	return (result);
}

struct dirent	**get_dirents(DIR *dir, int nb_dirents)
{
	struct dirent	**dirents;
	int				i;
	struct dirent	*dirent;

	dirents = malloc(nb_dirents * sizeof(struct dirent *));
	i = 0;
	dirent = readdir(dir);
	while (dirent != NULL && i < nb_dirents)
	{
		dirents[i] = dirent;
		i++;
		dirent = readdir(dir);
	}
	return (dirents);
}
