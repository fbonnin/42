#include "ls.h"

int		get_nb_blocks(char **elems, int nb_elems)
{
	int			result;
	int			i;
	struct stat	info;

	result = 0;
	i = 0;
	while (i < nb_elems)
	{
		lstat(elems[i], &info);
		result += info.st_blocks;
		i++;
	}
	return (result);
}

char	*strjoin3(char *s1, char *s2, char *s3)
{
	char *result;

	result = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
	ft_strcpy(result + ft_strlen(s1) + ft_strlen(s2), s3);
	return (result);
}
