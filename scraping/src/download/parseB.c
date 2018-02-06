#include "../scraping.h"

#define p text, &i_text, buffer

#define prefix "http://www.amf-france.org"

// analyse une page contenant un seul résultat
int	parseB(char *url_b, int i_pdf)
{
	char	*text;
	int		i_text;
	char	*buffer;
	char	*url_pdf;
	char	pdf_name[100];

	text = NULL;
	buffer = NULL;
	url_pdf = NULL;
	if (download(url_b, "pageB") == -1)
		return endB(text, buffer, url_pdf);
	text = load_file("pageB");
	if (text == NULL)
		return endB(text, buffer, url_pdf);
	i_text = 0;
	buffer = malloc(strlen(text) + 1);
	if (buffer == NULL)
		return endB(text, buffer, url_pdf);
	read_until(p, "Document AMF");
	read_until(p, "href");
	read_until(p, "\"");
	i_text++;
	read_until(p, "\"");
	url_pdf = malloc(strlen(prefix) + strlen(buffer) + 1);
	sprintf(url_pdf, "%s%s", prefix, buffer);
	sprintf(pdf_name, "pdf/%.5d.pdf", i_pdf);
	if (download(url_pdf, pdf_name) == -1)
		return endB(text, buffer, url_pdf);
	parse_pdf(pdf_name, "database.csv", url_pdf);
	endB(text, buffer, url_pdf);
	return 0;
}

int	endB(char *text, char *buffer, char *url_pdf)
{
	free(url_pdf);
	free(buffer);
	free(text);
	remove("pageB");
	return -1;
}
