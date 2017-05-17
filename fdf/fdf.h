#define FDF_ERROR -1

typedef struct	s_xy_int
{
	int x;
	int y;
}				t_xy_int;

typedef struct	s_xy_double
{
	double x;
	double y;
}				t_xy_double;

typedef struct	s_xyz_double
{
	double x;
	double y;
	double z;
}				t_xyz_double;

typedef struct s_point
{
	t_xyz_double	position1;
	t_xyz_double	position2;
	t_xy_double		position3;
	t_xy_int		position4;
}				t_point;

typdef struct s_s
{
	t_xyz_double pov;
	int		width;
	int		height;
	int		color;
	void	*mlx;
	void	*window;
	void	*image;
	char	*file_name;
	int		fd;
	int		nb_rows;
	int		nb_cols;
	t_point	**points;
	t_xyz_double	u;
	t_xyz_double	v;
	double	max_x3;
	double	max_y3;
}			t_s;
