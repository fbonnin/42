#include "ls.h"

void	sort_elems(char **elems, int nb_elems, int _t, int _r)
{
	if (_t)
		sort_elems_2(elems, nb_elems, is_lower_mtime, _r);
	else
		sort_elems_2(elems, nb_elems, is_lower_name, _r);
}

void	sort_elems_2(char **elems, int nb_elems,
int (*is_lower)(char *elem1, char *elem2), int _r)
{
	int		i;
	int		j;
	char	*elem;

	i = 1;
	while (i < nb_elems)
	{
		j = i;
		while (j > 0 && (
		(!_r && is_lower(elems[j], elems[j - 1])) ||
		(_r && is_lower(elems[j - 1], elems[j]))))
		{
			elem = elems[j - 1];
			elems[j - 1] = elems[j];
			elems[j] = elem;
			j--;
		}
		i++;
	}
}

int		is_lower_name(char *elem1, char *elem2)
{
	return (ft_strcmp(elem1, elem2) < 0);
}

int		is_lower_mtime(char *elem1, char *elem2)
{
	struct stat info1;
	struct stat info2;
	stat(elem1, &info1);
	stat(elem2, &info2);
	return (info1.st_mtime > info2.st_mtime);
}
