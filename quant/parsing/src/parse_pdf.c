#include "../parsing.h"

int	parse_pdf(char *input, char *output, char *lien)
{
	char			*text;
	t_notification	notification;

	text = NULL;
	init_notification(&notification);
	notification.lien = strdup(lien);
	if (pdf_to_text(input) == -1)
		return end(text, &notification, "pdf to text\n");
	text = load_file(input);
	remove(input);
	if (text == NULL)
		return end(text, &notification, "load text\n");
	if (extract_data(text, &notification) == -1)
		return end(text, &notification, "extract data\n");
	if (write_notification(&notification, output) == -1)
		return end(text, &notification, "write notification\n");
	end(text, &notification, "");
	return 0;
}

int	end(char *text, t_notification *notification, char *s)
{
	free_notification(notification);
	free(text);
	printf("%s", s);
	return -1;	
}
