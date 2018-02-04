int	parseB(CURL *session, char *linkB, int i_pdf)
{
	char	*text;
	int		i_text;
	char	*buffer;
	char	*linkPDF;
	char	pdf_name[100];

	text = NULL;
	buffer = NULL;
	linkPDF = NULL;
	if (download(session, linkB, "pageB") == -1)
		return endB(text, buffer, linkPDF);
	text = load_file("pageB");
	if (text == NULL)
		return endB(text, buffer, linkPDF);
	i_text = 0;
	buffer = malloc(strlen(text) + 1);
	if (buffer == NULL)
		return endB(text, buffer, linkPDF);
	read_until(p, "Document AMF");
	read_until(p, "href");
	read_until(p, "\"");
	i_text++;
	read_until(p, "\"");
	linkPDF = duptrim(buffer);
	itoa(i_pdf, pdf_name, 10);
	strcat(pdf_name, ".pdf");
	if (download(session, linkPDF, pdf_name) == -1)
		return endB(text, buffer, linkPDF);
	endB(text, buffer, linkPDF);
	return 0;
}

int	endB(char *text, char *buffer, char *linkPDF)
{
	free(linkPDF);
	free(buffer);
	free(text);
	remove("pageB");
	return -1;
}
