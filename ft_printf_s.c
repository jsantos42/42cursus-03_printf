#include "ft_printf.h"

void	print_string(char **str, va_list args, t_flags *flags)
{
	char	*string;
	int		heap;

	string = va_arg(args, char *);
	heap = 0;
	flags->len = ft_strlen(string);
	if (flags->precision >= 0 && flags->precision < flags->len)
	{
		flags->len = flags->precision;
		string = ft_substr(string, 0, flags->precision);
		heap = 1;
	}
	if (flags->left_justify != 0)
	{
		ft_putstr_fd(string, 1);
		padding(flags);
		flags->printed_chars += flags->len;
	}
	else
	{
		padding(flags);
		ft_putstr_fd(string, 1);
		flags->printed_chars += flags->len;
	}
	(*str)++;
	if (heap)
		free(string);
}
