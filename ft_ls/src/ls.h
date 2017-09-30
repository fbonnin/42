#ifndef LS_H
# define LS_H

# include "dirent.h"
# include "libft/libft.h"
# include "sys/stat.h"
# include "pwd.h"
# include "grp.h"
# include "time.h"

typedef struct	s_options
{
	int a;
	int l;
	int r;
	int R;
	int t;
}				t_options;

void			init_ls(int ac, char ***names,
					int *nb_names, t_options *options);
int				parse_av(char **names, int *nb_names,
					t_options *options, char *av);
int				parse_option(t_options *options, char option);
int				end_ls(char **names);

void			ls_names(char **names, int nb_names, t_options options);
void			ls_files(char **names, int nb_names,
					t_options options, int *first);
void			ls_dirs(char **names, int nb_names,
					t_options options, int first);
void			ls_dir(char *name, t_options options);
void			free_elems(char **elems, int nb_elems);
void			ls_subdirs(t_options options, char **elems, int nb_elems);

void			print_file(char *name, int _l);
void			print_info(struct stat info);
void			print_type(mode_t m);
void			print_permissions(mode_t m);
void			print_elems(char **elems, int nb_elems, int _l);

int				get_nb_elems(char *name, int _a);
char			**get_elems(char *name, int nb_elems, int _a);
char			*strjoin3(char *s1, char *s2, char *s3);
int				get_nb_blocks(char **elems, int nb_elems);

void			sort_elems(char **elems, int nb_elems, int _t, int _r);
void			sort_elems_2(char **elems, int nb_elems,
					int (*is_lower)(char *elem1, char *elem2), int _r);
int				is_lower_name(char *elem1, char *elem2);
int				is_lower_mtime(char *elem1, char *elem2);
int				strcmp_ls(const char *s1, const char *s2);

#endif
