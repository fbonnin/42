/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:54:00 by fbonnin           #+#    #+#             */
/*   Updated: 2017/10/06 16:00:30 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "dirent.h"
# include "sys/stat.h"
# include "pwd.h"
# include "grp.h"
# include "time.h"
# include "libft/libft.h"
# include "sys/types.h"

typedef struct	s_options
{
	int a;
	int l;
	int r;
	int rr;
	int t;
}				t_options;

int				init_ls(int ac, char ***params,
					int *nb_params, t_options *options);
int				parse_av(char **params, int *nb_params,
					t_options *options, char *av);
int				parse_option(t_options *options, char option);
int				end_ls(char **params);

void			ls_params(char **params, int nb_params, t_options options);
void			ls_dir(char *dir_name, t_options options);
void			ls_subdirs(t_options options, char **elems, int nb_elems);
void			print_non_existent(char **params, int nb_params);

char			**get_files(char **params, int nb_params, int *nb_files);
char			**get_dirs(char **params, int nb_params, int *nb_dirs);
int				get_nb_elems(char *dir_name, int a);
char			**get_elems(char *dir_name, int nb_elems, int a);
void			free_elems(char **elems, int nb_elems);

int				print_elems(char **elems, int nb_elems, t_options options);
int				print_elems_l(char **elems, int nb_elems);

char			get_type(struct stat info);
void			get_rights(struct stat info, char *rights);

char			***alloc_table(int nb_rows);
void			free_table(char ***table, int nb_rows);

int				fill_table(char **elems, int nb_elems, char ***table);
int				get_width(char ***table, int nb_rows, int i_col);
void			print_table(char ***table, int nb_rows, int *widths);

int				get_row_1(struct stat info, char **row);
int				get_row_2(struct stat info, char **row);
int				get_row_3(char *elem, char **row);

void			sort_elems(char **elems, int nb_elems, int t, int r);
void			sort_elems_2(char **elems, int nb_elems,
					int (*is_lower)(char *elem1, char *elem2), int r);
int				is_lower_name(char *elem1, char *elem2);
int				is_lower_mtime(char *elem1, char *elem2);
int				strcmp_ls(const char *s1, const char *s2);

int				get_nb_blocks(char **elems, int nb_elems);
char			*strjoin3(char *s1, char *s2, char *s3);

#endif
