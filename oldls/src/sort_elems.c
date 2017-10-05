#include "ls.h"

void	sort_elems(char **elems, int nb_elems, int _t, int _r)
{
	sort_elems_2(elems, nb_elems, is_lower_name, 0);
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
	int i1;
	int i2;

	i1 = ft_strlen(elem1);
	while (i1 > 0 && elem1[i1 - 1] != '/')
		i1--;
	i2 = ft_strlen(elem2);
	while (i2 > 0 && elem2[i2 - 1] != '/')
		i2--;
	if (elem1[i1] == '.')
		i1++;
	if (elem2[i2] == '.')
		i2++;
	return (strcmp_ls(elem1 + i1, elem2 + i2) < 0);
}

int		is_lower_mtime(char *elem1, char *elem2)
{
	struct stat info1;
	struct stat info2;
	lstat(elem1, &info1);
	lstat(elem2, &info2);
	return (info1.st_mtime > info2.st_mtime);
}

int	strcmp_ls(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (ft_tolower(s1[i]) != 0 && ft_tolower(s2[i]) != 0 &&
	ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return ((int)(unsigned char)ft_tolower(s1[i]) -
	(int)(unsigned char)ft_tolower(s2[i]));
}
