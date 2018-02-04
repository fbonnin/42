#include "../download.h"

#define p text, &i_text, buffer

char	*parseA(CURL *session, char *linkA, int *i_pdf)
{
	char	*text;
	int		i_text;
	char	*buffer;
	char	*linkB;
	int		type;
	int		r;

	text = NULL;
	buffer = NULL;
	linkB = NULL;
	if (download(session, linkA, "pageA") == -1)
		return endA(text, buffer);
	text = load_file("pageA");
	if (text == NULL)
		return endA(text, buffer);
	i_text = 0;
	buffer = malloc(strlen(text) + 1);
	if (buffer == NULL)
		return endA(text, buffer);
	while (text[i_text] != 0)
	{
		read_until_2(p, "Document AMF", "<span class=\"suivant\">");
		type = -1;
		if (strequ(text + i_text, "Document AMF"))
			type = 0;
		else if (strequ(text + i_text, "<span class=\"suivant\">"))
			type = 1;
		read_until(p, "href");
		read_until(p, "\"");
		i_text++;
		read_until(p, "\"");
		if (type == 0)
		{
			linkB = malloc(strlen(prefix) + strlen(buffer) + 1);
			sprintf(linkB, "%s%s", prefix, buffer);
			r = parseB(session, linkB, *i_pdf);
			free(linkB);
			if (r == -1)
				return endA(text, buffer);
			(*i_pdf)++;
		}
		else if (type == 1)
		{
			linkB = strdup(buffer);
			endA(text, buffer);
			return linkB;
		}
	}
	return endA(text, buffer);
}

char	*endA(char *text, char *buffer)
{
	free(buffer);
	free(text);
	//remove("pageA");
	return NULL;
}
