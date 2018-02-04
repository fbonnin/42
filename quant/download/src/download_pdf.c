#include "../download.h"

int	download_pdf(char *link)
{
	CURL	*session;
	char	*linkA;
	int		i_pdf;
	char	*r;

	session = curl_easy_init();
	if (session == NULL)
		return -1;
	linkA = strdup(link);
	i_pdf = 0;
	while (linkA != NULL)
	{
		r = parseA(session, linkA, &i_pdf);
		free(linkA);
		linkA = r;
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
		return -1;
	fclose(file);
	return 0;
}
