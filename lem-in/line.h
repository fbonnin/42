typedef struct	s_line
{
	char 			*str;
	struct s_line	*next;
}				t_line;

typedef struct	s_lines
{
	t_line *first;
	t_line *last;
}				t_lines;
