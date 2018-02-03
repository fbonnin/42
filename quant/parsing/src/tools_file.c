#include "../parse_pdf.h"

// converti pdf en txt
int		pdf_to_text(char *input)
{
	char	*command;
	int		r;

	if (strlen(input) < 4)
		return -1;
	command = malloc(strlen("./pdftotext ") + strlen(input) + 1);
	if (command == NULL)
		return -1;
	strcpy(command, "./pdftotext ");
	strcat(command, input);
	r = system(command);
	free(command);
	if (r == -1)
		return -1;
	strcpy(input + strlen(input) - 4, ".txt");
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
