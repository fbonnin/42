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
	unsigned char	*bytecode;
	int				pc;
	int				i_line_byte;
	int				i_line;
	char			*line;

	t_call			*calls;

	int				nb_bytes;
}

int				get_opcode(t_asm *a);
long long		get_number(char **line, long long mini, long long maxi);
char			*get_label(char *line);

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
