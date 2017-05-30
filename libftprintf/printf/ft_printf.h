/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:59:01 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/29 20:48:29 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "stdarg.h"
# include "wchar.h"
# include "stdint.h"

# define PRINTF_BUFFER_SIZE 1000
# define PRINTF_MAX_WIDTH_LEN 10
# define PRINTF_MAX_PRECISION_LEN 10
# define PRINTF_ERROR -1

typedef struct	s_printf
{
	const char				*format;
	int						i_format;
	va_list					params;
	int						nb_chars_written;
	unsigned char			buffer[PRINTF_BUFFER_SIZE];
	int						i_buffer;
	int						nb_bytes_written;

	int						flag_minus;
	int						flag_zero;
	int						flag_sharp;
	int						flag_plus;
	int						flag_space;
	int						width;
	int						precision;
	int						size;
	char					type;

	wchar_t					c;

	char					*str;
	wchar_t					*wstr;
	int						len_str;

	unsigned long long int	ullint;
	long long int			llint;
	char					prefix[2];
	int						len_prefix;
	int						base;
	int						uppercase;
	char					*number;
	int						len_number;
	int						nb_zeroes;

	char					*bits;
	int						nb_bits;
	int						i_bit;
	char					utf8[9];
	int						i_utf8;
}				t_printf;

int				ft_printf(const char *format, ...);
int				ft_put_wchar_to_buffer(t_printf *s, unsigned int c, int w);

void			ft_get_flags(t_printf *s);
int				ft_get_width(t_printf *s);
int				ft_get_precision(t_printf *s);
void			ft_get_size(t_printf *s);
void			ft_get_size2(t_printf *s, const char *size);

int				ft_printf_c(t_printf *s, int w);
int				ft_type_c(t_printf *s);

int				ft_printf_str(t_printf *s);
int				ft_printf_wstr(t_printf *s);
int				ft_type_str(t_printf *s);

int				ft_printf_ullint(t_printf *s);
int				ft_printf_ullint2(t_printf *s, char *number);
int				ft_type_uint(t_printf *s);
int				ft_type_uint2(t_printf *s);

int				ft_printf_llint(t_printf *s);
int				ft_type_int(t_printf *s);

void			ft_type_n(t_printf *s);
void			ft_type_n2(t_printf *s);

int				ft_type_unknown(t_printf *s);

int				ft_put_utf8_to_buffer(t_printf *s);
int				ft_size_wchar(wchar_t c);

#endif
