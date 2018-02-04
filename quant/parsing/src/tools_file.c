#include "../parsing.h"

// converti pdf en txt
int		pdf_to_text(char *pdf_name, char *txt_name)
{
	char	*command;
	int		r;

	command = malloc(strlen("gs -sDEVICE=txtwrite -o ") +
	strlen(txt_name) + 1 + strlen(pdf_name) + 1);
	if (command == NULL)
		return -1;
	strcpy(command, "gs -sDEVICE=txtwrite -o ");
	strcat(command, txt_name);
	strcat(command, " ");
	strcat(command, pdf_name);
	r = system(command);
	free(command);
	if (r == -1)
		return -1;
	return 0;
}

// charge fichier dans string
char	*load_file(char *name)
{
	FILE	*file;
	int		length;
	char	*result;

	file = fopen(name, "rb");
	if (file == NULL)
		return NULL;
	if (fseek(file, 0, SEEK_END) != 0 ||
	(length = ftell(file)) < 0 ||
	fseek(file, 0, SEEK_SET) != 0 ||
	(result = malloc(length + 1)) == NULL)
		return NULL;
	result[length] = 0;
	if ((int)fread(result, 1, length, file) != length)
	{
		free(result);
		result = NULL;
	}
	fclose(file);
	return result;
}
