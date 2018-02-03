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
