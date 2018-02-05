#include "../scraping.h"

int		download_pdfs(char *url)
{
	char	*url_a;
	int		i_pdf;
	char	*next;

	system("mkdir pdf");
	url_a = strdup(url);
	i_pdf = 0;
	while (url_a != NULL)
	{
		next = parseA(url_a, &i_pdf);
		free(url_a);
		url_a = next;
	}
	return 0;
}

int		download(char *url, char *name)
{
	char	*command;
	int		r;

	command = malloc(strlen("wget \"") + strlen(url) + strlen("\" -O ") + strlen(name) + 1);
	if (command == NULL)
		return -1;
	sprintf(command, "wget \"%s\" -O %s", url, name);
	r = system(command);
	free(command);
	if (r == -1)
		return -1;
	return 0;
}

void	remove_amp(char *s)
{
	char	*s2;
	int		i;
	int		i2;

	s2 = strdup(s);
	s[0] = 0;
	i = 0;
	i2 = 0;
	while (i2 < (int)strlen(s2))
	{
		if (strequ(s2 + i2, "amp;"))
			i2 += 4;
		else
			s[i++] = s2[i2++];
	}
	free(s2);
}
