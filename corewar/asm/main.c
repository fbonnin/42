#include "asm.h"

void	find_nb_bytes_i_reg(int *nb_bytes_i_reg)
{
	*nb_bytes_i_reg = 1;
	while (pow(2, *nb_bytes_i_reg * 8 - 1) - 1 < REG_NUMBER)
		(*nb_bytes_i_reg)++;
}

void	init_asm(t_asm *a)
{
	a->bytecode = malloc((4 + PROG_NAME_LENGTH + 4 +
	4 + COMMENT_LENGTH + 4 + CHAMP_MAX_SIZE + 1 + 1 +
	4 * ft_max(nb_bytes_i_reg, ft_max(DIR_SIZE, IND_SIZE))) *
	sizeof(unsigned char));
	a->pc = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	a->i_line = 1;
	a->prog_name = NULL;
	a->description = NULL;
	a->declarations = NULL;
	a->calls = NULL;
}

int		end(t_asm *a, char *str, int output)
{
	free(a->bytecode);
	free(a->prog_name);
	free(a->description);
	free_declarations(a->declarations);
	free_calls(a->calls);
	ft_printf(output, "%s\n", str);
	return (0);
}
