#include "stdio.h"
#include "sys/stat.h"
#include "pwd.h"
#include "grp.h"
#include "time.h"

int main(int ac, char **av)
{
	struct stat file_info;
	mode_t m;
	struct passwd *user_info;
	struct group *group_info;

	stat(av[1], &file_info);
	m = file_info.st_mode;

	printf("Nom: %s\n", av[1]);

	printf("Type: ");
	if (S_ISREG(m))
		printf("regular file");
	else if (S_ISDIR(m))
		printf("directory");
	else if (S_ISCHR(m))
		printf("character device");
	else if (S_ISBLK(m))
		printf("block device");
	else if (S_ISFIFO(m))
		printf("FIFO");
	else if (S_ISLNK(m))
		printf("symbolic link");
	else if (S_ISSOCK(m))
		printf("socket");
	printf("\n");

	printf("Modes: ");
	printf(m & S_IRUSR ? "r" : "-");
	printf(m & S_IWUSR ? "w" : "-");
	printf(m & S_IXUSR ? "x" : "-");
	printf(m & S_IRGRP ? "r" : "-");
	printf(m & S_IWGRP ? "w" : "-");
	printf(m & S_IXGRP ? "x" : "-");
	printf(m & S_IROTH ? "r" : "-");
	printf(m & S_IWOTH ? "w" : "-");
	printf(m & S_IXOTH ? "x" : "-");
	printf("\n");

	printf("Nombre de liens: %lu\n", file_info.st_nlink);

	user_info = getpwuid(file_info.st_uid);
	printf("Proprietaire: %s\n", user_info->pw_name);

	group_info = getgrgid(file_info.st_gid);
	printf("Groupe: %s\n", group_info->gr_name);

	printf("Taille: %ld octets\n", file_info.st_size);

	char *date = ctime(&file_info.st_mtime) + 4;
	date[15] = 0;
	printf("Date de derniere modification: %s\n", date);

	return (0);
}
