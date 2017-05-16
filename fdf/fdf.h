#define ERROR -1

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
	t_xyz_double position1;
	t_xyz_double position2;
	t_xy_double position3;
	t_xy_int position4;
}				t_point;

typdef struct s_s
{
	int nb_rows;
	int nb_cols;
	t_point **points;
	t_xyz pov;
	t_xyz u;
	t_xyz v;
}
