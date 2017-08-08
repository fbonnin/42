#ifndef ASM_H
# define ASM_H

# define POW_2_63 9223372036854775808
# define _POW_2_63 -9223372036854775808

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

typedef struct	s_declaration
{
	char					*label;
	int						pc;
	struct s_declaration	*next;
}				t_declaration;

typedef struct	s_call
{
	char			*label;
	int				pc;
	int				i_line_byte;
	int				nb_bytes;
	int				i_line;
	struct s_call	*next;
}				t_call;

typedef struct	s_asm
{
	int				nb_bytes_i_reg;

	unsigned char	*bytecode;
	int				pc;
	int				i_line_byte;
	int				i_line;
	char			*line;
	int				i_op;
	unsigned char	types_byte;
	int				nb_bytes;

	t_call			*calls;
}

void			add_value_to_bytecode(unsigned char *bytecode,
				long long value, int nb_bytes);
void			add_value_to_bytecode_2(unsigned char *bytecode,
				int nb_bytes, int neg);
void			add_strings_to_bytecode(unsigned char *bytecode,
				char *prog_name, char *description);
void			write_bytecode(unsigned char *bytecode,
				int pc, char *input_name, int len);

int				get_opcode(t_asm *a);
long long		get_number(char **line, long long mini, long long maxi);
char			*get_label(char *line);

int				get_reg(t_asm *a);
int				get_dir(t_asm *a);
int				get_ind(t_asm *a);

int				get_param(t_asm *a, unsigned char *pow4, t_arg_type type);
int				get_params(t_asm *a);
int				get_instruction(t_asm *a);

char			*get_declaration(char **line);
t_declaration	*find_declaration(t_declaration *declarations, char *label);
int				add_declaration(t_declaration **declarations,
				char **line, int pc);
void			free_declarations(t_declaration *declarations);

char			*get_call(char **line);
int				add_call(t_asm *a);
int				replace_calls(unsigned char *bytecode,
				t_declaration *declarations, t_call *calls);
void			free_calls(t_call *calls);

#endif
