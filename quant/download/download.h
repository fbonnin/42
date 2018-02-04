#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "curl/curl.h"
#include "../tools/tools.h"

#define prefix "amf-france.org/"

int		download_pdf(char *link);
int		download(CURL *session, char *url, char *name);

char	*parseA(CURL *session, char *linkA, int *i_pdf);
char	*endA(char *text, char *buffer);

int		parseB(CURL *session, char *linkB, int i_pdf);
int		endB(char *text, char *buffer, char *linkPDF);

#endif
