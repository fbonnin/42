#include "../scraping.h"

#define p text, &i_text, buffer

int extract_data(char *text, t_notification *n)
{
	int				i_text;
	char			*buffer;
	t_transaction	t;

	i_text = 0;
	buffer = malloc(strlen(text) + 1);
	if (buffer == NULL)
		return -1;
	read_until(p, "NOM");
	read_until(p, ":");
	i_text++;
	read_until(p, "NOTIFICATION");
	n->dirigeant = duptrim(buffer);
	read_until(p, ":");
	i_text++;
	read_until(p, "COORDONNEES");
	n->type = duptrim(buffer);
	read_until(p, "NOM");
	read_until(p, ":");
	i_text++;
	read_until_2(p, "LEI", "DETAIL");
	n->emetteur = duptrim(buffer);
	read_until(p, "DETAIL");
	while (strncmp(text + i_text, "DETAIL", strlen("DETAIL")) == 0)
	{
		read_until(p, "DATE");
		read_until(p, ":");
		i_text++;
		read_until(p, "LIEU");
		t.date = duptrim(buffer);
		read_until(p, ":");
		i_text++;
		read_until(p, "NATURE");
		t.lieu = duptrim(buffer);
		read_until(p, ":");
		i_text++;
		read_until(p, "DESCRIPTION");
		t.nature = duptrim(buffer);
		read_until(p, ":");
		i_text++;
		read_until_2(p, "CODE", "INFORMATION");
		t.instrument = duptrim(buffer);
		read_until(p, "PRIX");
		read_until(p, ":");
		i_text++;
		read_until(p, "VOLUME");
		t.prix = duptrim(buffer);
		read_until(p, ":");
		i_text++;
		read_until(p, "INFORMATION");
		t.volume = duptrim(buffer);
		read_until(p, "TRANSACTION");
		read_until(p, ":");
		i_text++;
		read_until_2(p, "DETAIL", "DATE");
		t.lie = duptrim(buffer);
		if (n->nb_transactions < MAX_TRANSACTIONS)
			n->transactions[n->nb_transactions++] = t;
	}
	read_until(p, ":");
	i_text++;
	read_until(p, "COMMENTAIRE");
	n->date = duptrim(buffer);
	read_until(p, ":");
	i_text++;
	read_until(p, "\"");
	n->commentaires = duptrim(buffer);
	return 0;
}
