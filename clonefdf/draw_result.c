void	draw_result(t_s *s)
{
	clear_image(s);
	draw_segments(s);
}

void	draw_segments(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			if (col < s->nb_cols - 1)
				draw_segment(s, s->points[row][col].position4, s->points[row][col + 1].position4);
			if (row < s->nb_rows - 1)
				draw_segment(s, s->points[row][col].position4, s->points[row + 1][col].position4);
			col++;
		}
		row++;
	}	
}

void	draw_segment(t_s *s, t_xy pixel1, t_xy pixel2)
{
	if (fabs(pixel1.x - pixel2.x) > fabs(pixel1.y - pixel2.y))
		draw_segment_horizontal(s, pixel1, pixel2);
	else
		draw_segment_vertical(s, pixel1, pixel2);
}

void	draw_segment_horizontal(t_s *s, t_xy pixel1, t_xy pixel2)
{
	t_xy	left;
	t_xy	right;
	double	a;
	double	b;
	double	x;

	if (pixel1.x < pixel2.x)
	{
		left = pixel1;
		right = pixel2;
	}
	else
	{
		left = pixel2;
		right = pixel1;
	}
	a = (right.y - left.y) / (right.x - left.x);
	b = pixel1.y - a * pixel1.x;
	x = left.x;
	while (x <= right.x)
	{
		image_pixel_put(x, a * x + b);
		x++;
	}
}

void	draw_segment_vertical(t_s *s, t_xy pixel1, t_xy pixel2)
{
	t_xy	top;
	t_xy	bottom;
	double	a;
	double	b;
	double	y;

	if (pixel1.y < pixel2.y)
	{
		top = pixel1;
		bottom = pixel2;
	}
	else
	{
		top = pixel2;
		bottom = pixel1;
	}
	a = (bottom.x - top.x) / (bottom.y - top.y);
	b = pixel1.x - a * pixel1.y;
	y = top.y;
	while (y <= bottom.y)
	{
		image_pixel_put(a * y + b, y);
		y++;
	}
}
