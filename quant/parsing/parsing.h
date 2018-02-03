#ifndef PARSING_H
#define PARSING_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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
int				parse_pdf(char *input, char *output, char *lien);
int				end(char *text, t_notification *notification, char *s);

				// notification.c
void			init_transaction(t_transaction *t);
void			free_transaction(t_transaction *t);
void			init_notification(t_notification *n);
void			free_notification(t_notification *n);
int				write_notification(t_notification *n, char *output);

				// tools_file.c
int				pdf_to_text(char *input);
char			*load_file(char *name);

				// extract_data.c
int				extract_data(char *text, t_notification *n);

				// tools_parsing.c
void			read_until(char *text, int *i_text, char *buffer, char *end);
void			read_until_2(char *text, int *i_text, char *buffer, char *end1, char *end2);
int				useless_char(char c);
char			*duptrim(char *s);

#endif
