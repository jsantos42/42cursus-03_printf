#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct s_flags {
	int		left_justify;
	char	padding;
	int		min_width;
	int		precision;
	int		len;
	char	*hex_case;
	int		printed_chars;
}	t_flags;

int		ft_printf(const char *input, ...);
void	reading(char **str, int *count);
int		check_flags(char **str, va_list args, t_flags *flags);
void	choose_conv(char **str, va_list args, t_flags *flags);
void	print_char(char **str, va_list args, t_flags *flags);
void	print_int(char **str, va_list args, t_flags *flags);
void	print_address(char **str, va_list args, t_flags *flags);
void	print_string(char **str, va_list args, t_flags *flags);
void	print_hex(char **str, va_list args, t_flags *flags);
void	print_unsigned_int(char **str, va_list args, t_flags *flags);
int		get_number(char **str, va_list args);
char	*check_precision(char *string, t_flags *flags);
char	*hex_converter(size_t decimal, t_flags *flags);
void	padding(t_flags *flags);
void	str_printer(char *str, t_flags *flags);
char	*unsigned_itoa(unsigned int n);

#endif
