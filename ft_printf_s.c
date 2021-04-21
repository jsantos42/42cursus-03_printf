#include "ft_printf.h"

void	print_string(char **str, va_list args, t_flags *flags)
{
	char	*string;
	int		heap;

	string = va_arg(args, char *);
	if (string == NULL)
		string = "(null)";
	heap = 0;
	flags->len = ft_strlen(string);
	if (flags->precision >= 0 && flags->precision < flags->len) {
		flags->len = flags->precision;
		string = ft_substr(string, 0, flags->precision);
		heap = 1;
	}
	str_printer(string, flags);
	(*str)++;
	if (heap)
		free(string);
}
