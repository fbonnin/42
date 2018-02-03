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
	if (fread(result, 1, length, file) != length)
	{
		free(result);
		result = NULL;
	}
	fclose(file);
	return result;
}

void	read_until(char *text, int *i_text, char *buffer, char *end)
{
	int i;

	i = 0;
	while (text[*i_text] != 0 &&
	strcmp(text + *i_text, end) != 0)
		buffer[i++] = text[(*i_text)++];
	buffer[i] = 0;
}

void	read_until_2(char *text, int *i_text, char *buffer, char *end1, char *end2)
{
	int i;

	i = 0;
	while (text[*i_text] != 0 &&
	strcmp(text + *i_text, end1) != 0 &&
	strcmp(text + *i_text, end2) != 0)
		buffer[i++] = text[(*i_text)++];
	buffer[i] = 0;
}

int		useless_char(char c)
{
	return c < 32;
}

char	*duptrim(char *s)
{
	char	*result;
	int		i1;
	int		i2;
	int		length;
	int		i;

	i1 = 0;
	while (useless_char(s[i1]))
		i1++;
	i2 = strlen(s) - 1;
	while (i2 >= 0 && useless_char(s[i2]))
		i2--;
	length = i2 - i1 + 1;
	if (length < 0)
		length = 0;
	result = malloc(length + 1);
	result[length] = 0;
	i = 0;
	while (i1 + i <= i2)
	{
		result[i] = s[i1 + i];
		i++;
	}
	return result;
}

