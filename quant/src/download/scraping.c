#include "../scraping.h"

int		scrape(char *url)
{
	char	*url_a;
	int		i_pdf;
	char	*next;

	remove("database.csv");
	system("mkdir pdf");
	url_a = strdup(url);
	i_pdf = 0;
	while (url_a != NULL && i_pdf < 546 * 10)
	{
		next = parseA(url_a, &i_pdf);
		free(url_a);
		url_a = next;
	}
	free(url_a);
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
