#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "../tools/tools.h"
#include "../parsing/parsing.h"

int		download_pdfs(char *url);
int		download(char *url, char *name);
void	remove_amp(char *s);

char	*parseA(char *url_a, int *i_pdf);
char	*endA(char *text, char *buffer);

int		parseB(char *url_b, int i_pdf);
int		endB(char *text, char *buffer, char *url_pdf);

#endif
