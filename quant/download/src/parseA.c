#include "../download.h"

#define p text, &i_text, buffer

char	*parseA(CURL *session, char *linkA, int *i_pdf)
{
	char	*text;
	int		i_text;
	char	*buffer;
	char	*linkB;

	text = NULL;
	buffer = NULL;
	linkB = NULL;
	if (download(session, linkA, "pageA") == -1)
		return endA(text, buffer, linkB);
	text = load_file("pageA");
	if (text == NULL)
		return endA(text, buffer, linkB);
	i_text = 0;
	buffer = malloc(strlen(text) + 1);
	if (buffer == NULL)
		return endA(text, buffer, linkB);
	while (text[i_text] != 0)
	{
		read_until_2(p, "Document AMF", "<span class=\"suivant\">");
		read_until(p, "href");
		read_until(p, "\"");
		i_text++;
		read_until(p, "\"");
		linkB = duptrim(buffer);
		if (strequ(text + i_text, "Document AMF"))
		{
			if (parseB(session, linkB, *i_pdf) == -1)
				return endA(text, buffer, linkB);
			free(linkB);
			(*i_pdf)++;
		}
		else if (strequ(text + i_text, "<span class=\"suivant\">"))
		{
			endA(text, buffer, linkB);
			return linkB;
		}
	}
	return endA(text, buffer, linkB);
}

char	*endA(char *text, char *buffer, char *linkB)
{
	free(linkB);
	free(buffer);
	free(text);
	remove("pageA");
	return NULL;
}
