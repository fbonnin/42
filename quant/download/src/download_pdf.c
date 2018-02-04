#include "../download.h"

void	check_next(char *s)
{
	char *cpy;
	int i;	

	cpy = strdup(s);
	s[0] = 0;
	i = 0;
	while (i < (int)strlen(cpy))
	{
		if (strequ(cpy + i, "amp;"))
			i += 3;
		else
		{
			sprintf(s + strlen(s), "%c", cpy[i]);
		}
		i++;
	}
	free(cpy);
}

int	download_pdf(char *link)
{
	CURL	*session;
	char	*linkA;
	int		i_pdf;
	char	*r;

	session = curl_easy_init();
	if (session == NULL)
		return -1;
	system("mkdir pdf");
	linkA = strdup(link);
	i_pdf = 0;
	while (linkA != NULL)
	{
		r = parseA(session, linkA, &i_pdf);
		free(linkA);
		linkA = r;
		check_next(linkA);
	}
	curl_easy_cleanup(session);
	return 0;
}

int	download(char *url, char *name)
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
