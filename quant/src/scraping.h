#ifndef SCRAPING_H
#define SCRAPING_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


// DOWNLOAD

// scraping.c
int				scrape(char *url);
int				download(char *url, char *name);

// parseA.c
char			*parseA(char *url_a, int *i_pdf);
char			*endA(char *text, char *buffer);
void			remove_amp(char *s);

// parseB.c
int				parseB(char *url_b, int i_pdf);
int				endB(char *text, char *buffer, char *url_pdf);


// PARSING

#define MAX_TRANSACTIONS 1000

typedef struct	s_transaction
{
	char *date;
	char *lieu;
	char *nature;
	char *instrument;
	char *prix;
	char *volume;
	char *lie;
}				t_transaction;

typedef struct	s_notification
{
	char			*dirigeant;
	char			*type;
	char			*emetteur;
	t_transaction	transactions[MAX_TRANSACTIONS];
	int				nb_transactions;
	char			*date;
	char			*commentaires;
	char			*lien;
}				t_notification;

				// parse_pdf.c
int				parse_pdf(char *pdf_name, char *output_name, char *lien);
int				end(char *txt_name, char *text, t_notification *notification, char *s);
int				pdf_to_text(char *pdf_name, char *txt_name);

				// notification.c
void			init_transaction(t_transaction *t);
void			free_transaction(t_transaction *t);
void			init_notification(t_notification *n);
void			free_notification(t_notification *n);
int				write_notification(t_notification *n, char *output);

				// extract_data.c
int				extract_data(char *text, t_notification *n);


// TOOLS

char			*load_file(char *name);
void			read_until(char *text, int *i_text, char *buffer, char *end);
void			read_until_2(char *text, int *i_text, char *buffer, char *end1, char *end2);
int				strequ(char *s1, char *s2);
char			*duptrim(char *s);
int				useless_char(char c);

#endif
