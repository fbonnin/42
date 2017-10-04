int	get_row_1(struct stat info, char **row)
{
	struct passwd	*usr;
	struct group	*grp;

	if ((row[0] = ft_strnew(10)) == NULL)
		return (-1);
	row[0][0] = get_type(info);
	get_rights(info, row[0] + 1);
	if ((row[1] = ft_itoa(info.nlink)) == NULL)
		return (-1);
	if ((usr = getpwuid(info.st_uid)) == NULL)
		return (-1);
	if ((row[2] = ft_strdup(usr->pw_name)) == NULL)
		return (-1);
	if ((grp = getgrgid(info.st_gid)) == NULL)
		return (-1);
	if ((row[3] = ft_strdup(grp->gr_name)) == NULL)
		return (-1);
	return (0);
}
