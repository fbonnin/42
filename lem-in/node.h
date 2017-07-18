typedef struct	s_neighbor
{
	int					i_node;
	struct s_neighbor	*next;
}				t_neighbor;

typedef struct	s_node
{
	char 		*name;
	t_neighbor	*neighbors;
	int			time_available;
	int			reached;
	int			time_reach;
	int			previous;
}				t_node;
