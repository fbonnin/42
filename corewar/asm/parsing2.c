#include "asm.h"

int	get_reg(t_asm *a)
{
	long long reg;

	if (a->line[0] != 'r')
		return (-1);
	a->line++;
	reg = get_number(&a->line, 1, REG_NUMBER);
	if (reg == -pow(2, 63))
	{
		ft_printf(2, "Invalid register\n");
		a->line--;
		return (-2);
	}
	add_value_to_bytecode(a->bytecode + a->pc + a->i_line_byte,
	reg, a->nb_bytes_i_reg);
	a->i_line_byte += a->nb_bytes_i_reg;
	return (0);
}

int	get_dir(t_asm *a)
{
	long long dir;

	if (a->line[0] != '%')
		return (-1);
	a->line++;
	a->nb_bytes = DIR_SIZE;
	if (op_tab[a->i_op].index_expected)
		a->nb_bytes = IND_SIZE;
	dir = get_number(&a->line,
	(a->nb_bytes >= 8 ? _POW_2_63 + 1 : -pow(2, a->nb_bytes * 8 - 1),
	(a->nb_bytes >= 8 ? POW_2_63 - 1 : pow(2, a->nb_bytes * 8 - 1) - 1));
	if (dir == _POW_2_63)
	{
		if (add_call(a) == 0)
		{
			a->line--;
			return (-1);
		}
	}
	else
		add_value_to_bytecode(a->bytecode + a->pc + a->i_line_byte,
		dir, a->nb_bytes);
	a->i_line_byte += a->nb_bytes;
	return (0);
}

int	get_ind(t_asm *a)
{
	long long ind;

	ind = get_number(&a->line,
	(IND_SIZE >= 8 ? _POW_2_63 + 1 : -pow(2, IND_SIZE * 8 - 1)),
	(IND_SIZE >= 8 ? POW_2_63 - 1 : pow(2, IND_SIZE * 8 - 1) - 1));
	if (ind == _POW_2_63)
	{
		a->nb_bytes = IND_SIZE;
		if (add_call(a) == 0)
			return (-1);
	}
	else
		add_value_to_bytecode(a->bytecode + a->pc + a->i_line_byte,
		ind, IND_SIZE);	
	a->i_line_byte += IND_SIZE;
	return (0);
}