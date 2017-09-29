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
void			ls_subdirs(char *name, t_options options,
					struct dirent **dirents, int nb_dirents);

void			print_file(char *name, int _l);
void			print_info(struct stat info);
void			print_type(mode_t m);
void			print_permissions(mode_t m);
void			print_dirents(struct dirent **dirents, int nb_dirents, int _l);

int				get_nb_dirents(DIR *dir, int _a);
struct dirent	**get_dirents(DIR *dir, int nb_dirents, int _a);

void			sort_dirents(struct dirent **dirents, int nb_dirents,
					int _t, int _r);
void			sort_dirents_2(struct dirent **dirents, int nb_dirents,
					int (*is_lower)(struct dirent *dirent1,
					struct dirent *dirent2), int _r);
int				is_lower_name(struct dirent *dirent1, struct dirent *dirent2);
int				is_lower_mtime(struct dirent *dirent1, struct dirent *dirent2);

#endif
