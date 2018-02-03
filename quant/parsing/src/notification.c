#include "../parse_pdf.h"

void	init_transaction(t_transaction *t)
{
	t->date = NULL;
	t->lieu = NULL;
	t->nature = NULL;
	t->instrument = NULL;
	t->prix = NULL;
	t->volume = NULL;
	t->lie = NULL;
}

void	free_transaction(t_transaction *t)
{
	free(t->date);
	free(t->lieu);
	free(t->nature);
	free(t->instrument);
	free(t->prix);
	free(t->volume);
	free(t->lie);
}

void	init_notification(t_notification *n)
{
	int i;

	n->dirigeant = NULL;
	n->type = NULL;
	n->emetteur = NULL;
	i = 0;
	while (i < MAX_TRANSACTIONS)
	{
		init_transaction(&n->transactions[i]);
		i++;
	}
	n->nb_transactions = 0;
	n->date = NULL;
	n->commentaires = NULL;
	n->lien = NULL;
}

void	free_notification(t_notification *n)
{
	int i;

	free(n->dirigeant);
	free(n->type);
	free(n->emetteur);
	i = 0;
	while (i < MAX_TRANSACTIONS)
	{
		free_transaction(&n->transactions[i]);
		i++;
	}
	free(n->date);
	free(n->commentaires);
	free(n->lien);
}

int		write_notification(t_notification *n, char *output)
{
	FILE			*file;
	t_transaction	*t;
	int				i;

	file = fopen(output, "a");
	if (file == NULL)
		return -1;
	i = 0;
	while (i < n->nb_transactions)
	{
		t = &n->transactions[i];
		fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
		n->dirigeant, n->type, n->emetteur,
		t->date, t->lieu, t->nature,
		t->instrument, t->prix, t->volume, t->lie,
		n->date, n->commentaires, n->lien);
		i++;
	}
	fclose(file);
	return 0;
}
