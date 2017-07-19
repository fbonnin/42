#ifndef LEM-IN_H
# define LEM-IN_H

#include "line.h"
#include "node.h"
#include "move.h"

typedef struct	s_s
{
	t_lines 		lines;
	int				nb_lines;
	int				nb_ants;
	t_node			*nodes;
	int				nb_nodes_expected;
	int				nb_nodes;
	t_list_moves	list_moves;
	t_move			*moves;
}				t_s;

t_line			*alloc_line();
void			add_line(t_lines *lines, char *str);
void			free_lines(t_lines *lines);
void			print_lines(t_lines lines, int nb_lines);

void			get_input(t_lines *lines, int *nb_nodes_expected);
void			get_part1(int *nb_nodes_expected,
				char *str, int *stop, int *part);
void			get_part2(char *str, int *stop);
void			free_words(char **words);

void			alloc_nodes(t_node **nodes, int nb_nodes_expected);
void			free_nodes(t_node **nodes, int nb_nodes_expected);
int				name_to_index(t_node *nodes, int nb_nodes, char *name);

t_neighbor		*alloc_neighbor();
void			add_neighbor(t_neighbor **neighbors, int i_neighbor);
void			free_neighbors(t_neighbor **neighbors);

void			parse_lines(t_s *s);
int				parse_sharp(t_node *nodes, char *str, int *stop, int *cmd);
int				parse_part0(int *nb_ants, char *str, int *stop, int *part);
int				parse_part1(t_node *nodes, int *nb_nodes, char *str, int *cmd);
void			parse_part2(t_node *nodes, int nb_nodes, char *str, int *stop);

int				find_path(t_node *nodes, int nb_nodes,
				t_list_moves *list_moves, int ant)
void			initialize_bfs(t_node *nodes, int nb_nodes);
int				find_closest(t_node *nodes, int nb_nodes);
void			reach(t_node *nodes, int i_node);
void			save_moves(t_node *nodes, t_list_moves *list_moves, int ant);

t_list_move		*alloc_list_move();
void			add_list_move(t_list_moves *list_moves, t_move move);
void			free_list_moves(t_list_moves *list_moves);

t_move			*list_moves_to_moves(t_list_moves *list_moves);
void			sort_moves(t_move *moves, int nb_moves);
void			print_moves(t_move *moves, int nb_moves);

#endif