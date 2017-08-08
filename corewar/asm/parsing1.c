#include "asm.h"

int		get_opcode(t_asm *a)
{
	int 	i;
	char	*name;
	int		len;

	i = 0;
	while (op_tab[i].opcode != 0)
	{
		name = op_tab[i].name;
		len = ft_strlen(name);
		if (ft_strnequ(name, a->line, len) == 1 && a->line[len] == ' ')
		{
			a->line += len + 1;
			break ;
		}
		i++;
	}
	if (op_tab[i].opcode == 0)
		return (-1);
	a->i_op = i;
	add_value_to_bytecode(a->bytecode + a->pc, op_tab[i].opcode, 1);
	return (0);
}

long long get_number(char **line, long long mini, long long maxi)
{
	long long	result;
	int			sign;
	int			len;

	result = 0;
	sign = 1;
	len = 0;
	if (**line == '-' || **line == '+')
	{
		if (**line == '-')
			sign = -1;
		len = 1;
	}
	if (!ft_isdigit((*line)[len]))
		return (_POW_2_63);
	while (ft_isdigit((*line)[len]))
	{
		result *= 10;
		result += (*line)[len++] - 48;
	}
	result *= sign;
	if (result < mini ||result > maxi || result == _POW_2_63)
		return (_POW_2_63);
	*line += len;
	return (result);
}

char	*get_label(char *line)
{
	char	*result;
	int		len;
	int		i;

	if (ft_strchr(LABEL_CHARS, *line) == NULL || *line == 0)
		return (NULL);
	len = 0;
	while (ft_strchr(LABEL_CHARS, line[len]) != NULL && line[len] != 0)
		len++;
	result = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		result[i] = line[i];
		i++;
	}
	return (result);
}