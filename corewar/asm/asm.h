#ifndef ASM_H
# define ASM_H

typedef struct	s_op
{
	char		*name;
	int			nb_params;
	t_arg_type	*types;
	int			opcode;
	int			nb_cycles;
	char		*description;
	int			type_required;
	int			index_expected;
}				t_op;

typedef struct	s_asm
{
	unsigned char	*bytecode;
	int				pc;
	int				i_line_byte;
	int				i_line;
	char			*line;

	t_call			*calls;

	int				nb_bytes;
}

char			*get_call(char **line);
int				add_call(t_asm *a);
int				replace_calls(unsigned char *bytecode,
				t_declaration *declarations, t_call *calls);
void			free_calls(t_call *calls);

#endif
