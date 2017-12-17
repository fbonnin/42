/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 20:52:14 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 17:35:28 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MAX_TETRIS 26
# define BUFFER_SIZE 546

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_tetri
{
	t_point		**points;
	int			height;
	int			width;
	int			points_count;
	char		letter;
}				t_tetri;

typedef struct	s_grid
{
	char		**cells;
	int			max_size;
	int			min_size;
	int			nb_tetris;
}				t_grid;

int				get_splited_file(char *path, char ***tetris);
int				tetri_is_valide(char *buffer);
int				tetri_match_rules(char *tetri);
int				get_tetri(t_tetri **tetri, char *buffer);
int				parse_all_tetri(t_tetri ***tetris, char **splited, int count);
int				create_grid(t_tetri **tetris, int count, t_grid **grid);
int				scale_tetri(t_tetri *tetri);
void			clear_grid(t_grid **grid);
void			print_grid(t_grid *grid);
void			put_remove(t_grid *grid, t_point *pos, t_tetri *tetri, int op);
int				can_put(t_grid *grid, t_point *pos, t_tetri *tetri);
int				fill(t_grid *grid, t_tetri **tetri, int i_tetri);
int				find_min_square(t_grid *grid, t_tetri **tetris);

#endif
