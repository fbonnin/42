#include "../scraping.h"

#define p text, &i_text, buffer

#define prefix "http://www.amf-france.org"

// analyse une page contenant plusieurs résultats
char	*parseA(char *url_a, int *i_pdf)
{
	char	*text;
	int		i_text;
	char	*buffer;
	char	*url_b;
	int		type;
	int		r;

	text = NULL;
	buffer = NULL;
	if (download(url_a, "pageA") == -1)
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
			url_b = malloc(strlen(prefix) + strlen(buffer) + 1);
			sprintf(url_b, "%s%s", prefix, buffer);
			r = parseB(url_b, *i_pdf);
			free(url_b);
			if (r == -1)
				return endA(text, buffer);
			(*i_pdf)++;
		}
		else if (type == 1)
		{
			url_b = strdup(buffer);
			remove_amp(url_b);
			endA(text, buffer);
			return url_b;
		}
	}
	return endA(text, buffer);
}

char	*endA(char *text, char *buffer)
{
	free(buffer);
	free(text);
	remove("pageA");
	return NULL;
}

// supprime les "amp;" d'une url
void	remove_amp(char *s)
{
	char	*s2;
	int		i;
	int		i2;

	s2 = strdup(s);
	s[0] = 0;
	i = 0;
	i2 = 0;
	while (i2 <= (int)strlen(s2))
	{
		if (strequ(s2 + i2, "amp;"))
			i2 += 4;
		else
			s[i++] = s2[i2++];
	}
	free(s2);
}
