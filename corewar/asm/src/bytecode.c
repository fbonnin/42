#include "asm.h"

void	add_value_to_bytecode(unsigned char *bytecode,
long long value, int nb_bytes)
{
	int			i;
	int			neg;
	long long	pow256;

	neg = value < 0 ? 1 : 0;
	if (value < 0)
		value *= -1;
	i = 0;
	while (i < nb_bytes - 8)
		bytecode[i++] = 0;
	pow256 = ft_pow(256, nb_bytes - i - 1);
	while (pow256 > 0)
	{
		bytecode[i++] = value / pow256;
		value %= pow256;
		pow256 /= 256;
	}
	add_value_to_bytecode_2(bytecode, nb_bytes, neg);
}

void	add_value_to_bytecode_2(unsigned char *bytecode,
int nb_bytes, int neg)
{
	int i;

	if (!neg)
		return ;
	i = 0;
	while (i < nb_bytes)
	{
		bytecode[i] = ~bytecode[i];
		i++;
	}
	while (bytecode[--i] == 255)
		bytecode[i] = 0;
	bytecode[i]++;
}

void	add_strings_to_bytecode(unsigned char *bytecode,
char *prog_name, char *description)
{
	int i;

	i = 0;
	if (prog_name != NULL)
	{
		while (prog_name[i] != 0)
		{
			bytecode[4 + i] = prog_name[i];
			i++;
		}
	}
	while (i < PROG_NAME_LENGTH + 4)
		bytecode[4 + i++] = 0;
	i = 0;
	if (description != NULL)
	{
		while (description[i] != 0)
		{
			bytecode[4 + PROG_NAME_LENGTH + 4 + 4 + i] = description[i];
			i++;
		}
	}
	while (i < COMMENT_LENGTH + 4)
		bytecode[4 + PROG_NAME_LENGTH + 4 + 4 + i++] = 0;
}

void	write_bytecode(unsigned char *bytecode, int pc,
char *input_name, int len)
{
	char	*output_name;
	int		fd;

	input_name[len - 2] = 0;
	output_name = ft_strjoin(input_name, ".cor");
	fd = open(output_name, O_CREAT | O_WRONLY, 0777);
	free(output_name);
	if (fd == -1)
		return ;
	write(fd, bytecode, pc);
	close(fd);
}