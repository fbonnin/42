#include "../parsing.h"

int	parse_pdf(char *pdf_name, char *output_name, char *lien)
{
	char			*txt_name;
	char			*text;
	t_notification	notification;

	txt_name = NULL;
	text = NULL;
	init_notification(&notification);
	if (strlen(pdf_name) < 5)
		return end(txt_name, text, &notification, "error: pdf name\n");
	txt_name = strdup(pdf_name);
	strcpy(txt_name + strlen(txt_name) - 4, ".txt");
	notification.lien = strdup(lien);
	if (pdf_to_text(pdf_name) == -1)
		return end(txt_name, text, &notification, "error: pdf to text\n");
	text = load_file(txt_name);
	remove(txt_name);
	if (text == NULL)
		return end(txt_name, text, &notification, "error: load text\n");
	if (extract_data(text, &notification) == -1)
		return end(txt_name, text, &notification, "error: extract data\n");
	if (write_notification(&notification, output_name) == -1)
		return end(txt_name, text, &notification, "error: write notification\n");
	end(txt_name, text, &notification, "");
	return 0;
}

int	end(char *txt_name, char *text, t_notification *notification, char *s)
{
	free_notification(notification);
	free(text);
	free(txt_name);
	printf("%s", s);
	return -1;	
}
