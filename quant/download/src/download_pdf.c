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

int	download(CURL *session, char *url, char *name)
{
	FILE *file;

	file = fopen(name, "w");
	curl_easy_setopt(session, CURLOPT_URL, url);
	curl_easy_setopt(session, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, fwrite);
	if (curl_easy_perform(session) != 0)
	{
		fclose(file);
		return -1;
	}
	fclose(file);
	return 0;
}
