#ifndef TOOLS_H
#define TOOLS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char	*load_file(char *name);
void	read_until(char *text, int *i_text, char *buffer, char *end);
void	read_until_2(char *text, int *i_text, char *buffer, char *end1, char *end2);
int		strequ(char *s1, char *s2);
int		useless_char(char c);
char	*duptrim(char *s);

#endif
